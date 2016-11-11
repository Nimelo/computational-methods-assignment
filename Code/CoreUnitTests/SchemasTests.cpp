#include "SchemasTests.h"

#include "UpwindExplicitSchema.h"
#include "UpwindImplicitSchema.h"
#include "RichtmyerMultiStepSchema.h"
#include "LaxWendroffSchema.h"

#include "WavePoints.h"

TEST_F(SchemasTests, UpwindExplicitSchema)
{
	AbstractSchema * s = new UpwindExplicitSchema();

	WavePoints * prev = new WavePoints(5);
	WavePoints * c = new WavePoints(5);
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

	WavePoints * p = s->apply(prev, 4, 1, 1);

	ASSERT_EQ(true , SchemasTests::compare(p, c));
	delete s;
	delete prev;
	delete p;
	delete c;
}	

TEST_F(SchemasTests, LaxWendroffSchema)
{
	AbstractSchema * s = new LaxWendroffSchema();

	WavePoints * prev = new WavePoints(5);
	WavePoints * c = new WavePoints(5);
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
	WavePoints * p = s->apply(prev, 2, 1, 1);

	ASSERT_EQ(true, SchemasTests::compare(p, c));
	delete s;
	delete prev;
	delete p;
	delete c;
}

TEST_F(SchemasTests, UpwindImplicitSchema)
{
	AbstractSchema * s = new UpwindImplicitSchema();

	WavePoints * prev = new WavePoints(5);
	WavePoints * c = new WavePoints(5);

	for (unsigned int i = 0; i < 5; i++)
	{
		prev->at(i) = i;
	}

	(*c)[0] = (*prev)[0];
	(*c)[1] = 91.0 / 51;
	(*c)[2] = -8.0 / 51;
	(*c)[3] = 113.0 / 51;
	(*c)[4] = (*prev)[4];

	WavePoints * p = s->apply(prev, 1, 10, 1);
	delete s->apply(prev, 1, 10, 1);
	ASSERT_EQ(true, SchemasTests::compare(p, c, 0.01));
	delete s;
	delete prev;
	delete p;
	delete c;
}

TEST_F(SchemasTests, UpwindImplicitSchema2)
{
	AbstractSchema * s = new UpwindImplicitSchema();

	WavePoints * prev = new WavePoints(10);

	for (unsigned int i = 0; i < 10; i++)
	{
		prev->at(i) = 0;
	}

	try
	{
		delete s->apply(prev, (50.0 + 50.0) / 400.0, 0.58, 1.75);
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
	AbstractSchema * s = new RichtmyerMultiStepSchema();

	WavePoints * prev = new WavePoints(5);
	WavePoints * c = new WavePoints(5);
	for (unsigned int i = 0; i < 5; i++)
	{
		prev->at(i) = i;
		c->at(i) = i;
	}
	c->at(2) = 2.0 - 1.0 / 3.0;

	WavePoints * p = s->apply(prev, 3, 1, 1);

	ASSERT_EQ(true, SchemasTests::compare(p, c));
	delete s;
	delete prev;
	delete p;
	delete c;
}
