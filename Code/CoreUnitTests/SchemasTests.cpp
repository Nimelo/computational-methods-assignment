#include "SchemasTests.h"

#include <vector>

#include "UpwindExplicitSchema.h"
#include "UpwindImplicitSchema.h"
#include "RichtmyerMultiStepSchema.h"
#include "LaxWendroffSchema.h"


TEST_F(SchemasTests, UpwindExplicitSchema)
{
	AbstractSchema * s = new UpwindExplicitSchema(1, 4, 1);

	std::vector<double> * prev = new std::vector<double>(5);
	std::vector<double> * c = new std::vector<double>(5);
	for (unsigned int i = 0; i < 5; i++)
	{
		prev->at(i) = i;
		if (i == 0 || i == 4)
		{
			c->at(i) = i;
		}
		else
		{
			c->at(i) = i - 0.25;
		}
	}

	std::vector<double> * p = s->apply(prev);

	ASSERT_EQ(true , SchemasTests::compare(p, c));
	delete s;
	delete prev;
	delete p;
	delete c;
}	

TEST_F(SchemasTests, LaxWendroffSchema)
{
	AbstractSchema * s = new LaxWendroffSchema(1, 2, 1);

	std::vector<double> * prev = new std::vector<double>(5);
	std::vector<double> * c = new std::vector<double>(5);
	for (unsigned int i = 0; i < 5; i++)
	{
		prev->at(i) = i;
		if (i == 0 || i == 4)
		{
			c->at(i) = i;
		}
		else
		{
			c->at(i) = i - 0.5;
		}
	}
	std::vector<double> * p = s->apply(prev);

	ASSERT_EQ(true, SchemasTests::compare(p, c));
	delete s;
	delete prev;
	delete p;
	delete c;
}

TEST_F(SchemasTests, UpwindImplicitSchema)
{
	AbstractSchema * s = new UpwindImplicitSchema(10, 1, 1);

	std::vector<double> * prev = new std::vector<double>(5);
	std::vector<double> * c = new std::vector<double>(5);

	for (unsigned int i = 0; i < 5; i++)
	{
		prev->at(i) = i;
	}

	(*c)[0] = (*prev)[0];
	(*c)[1] = 91.0 / 51;
	(*c)[2] = -8.0 / 51;
	(*c)[3] = 113.0 / 51;
	(*c)[4] = (*prev)[4];

	std::vector<double> * p = s->apply(prev);
	delete s->apply(prev);
	ASSERT_EQ(true, SchemasTests::compare(p, c, 0.01));
	delete s;
	delete prev;
	delete p;
	delete c;
}

TEST_F(SchemasTests, UpwindImplicitSchema2)
{
	AbstractSchema * s = new UpwindImplicitSchema(0.58, (50.0 + 50.0) / 400.0, 1.75);

	std::vector<double> * prev = new std::vector<double>(10);

	for (unsigned int i = 0; i < 10; i++)
	{
		prev->at(i) = 0;
	}

	try
	{
		delete s->apply(prev);
		delete s;
		delete prev;
	}
	catch (ZeroPivotException & zpe)
	{	
		delete s;
		delete prev;
	}
}

TEST_F(SchemasTests, RichtmyerMultiStepSchema)
{
	AbstractSchema * s = new RichtmyerMultiStepSchema(1, 3, 1);

	std::vector<double> * prev = new std::vector<double>(5);
	std::vector<double> * c = new std::vector<double>(5);
	for (unsigned int i = 0; i < 5; i++)
	{
		prev->at(i) = i;
		c->at(i) = i;
	}
	c->at(2) = 2.0 - 1.0 / 3.0;

	std::vector<double> * p = s->apply(prev);

	ASSERT_EQ(true, SchemasTests::compare(p, c));
	delete s;
	delete prev;
	delete p;
	delete c;
}
