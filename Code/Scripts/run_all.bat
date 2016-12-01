powershell -command ".\RUN_ALL.ps1 -confDirectory "..\Configurations\impactExplicit\" -resultDirectory "..\results\impactExplicit\""
powershell .\RUN_ALL.ps1 -confDirectory "..\Configurations\impactImplicit\" -resultDirectory "..\results\impactImplicit\"
powershell .\RUN_ALL.ps1 -confDirectory "..\Configurations\impactLax-Wendroff\" -resultDirectory "..\results\impactLax-Wendroff\"
powershell .\RUN_ALL.ps1 -confDirectory "..\Configurations\impactRichtmyer-Multi-Step\" -resultDirectory "..\results\impactRichtmyer-Multi-Step\"

powershell .\RUN_ALL.ps1 -confDirectory "..\Configurations\changeInTime\" -resultDirectory "..\results\changeInTime\" -regex "*exp*"

powershell .\RUN_ALL.ps1 -resultDirectory "..\results\gridConvergence\" -regex "*exp*"

powershell .\RUN_ALL.ps1 -resultDirectory "..\results\comparision\" -regex "*400*"