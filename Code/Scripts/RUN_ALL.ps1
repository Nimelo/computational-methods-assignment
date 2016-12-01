param(
[string]$confDirectory="..\Configurations", 
[string]$confExtension="conf",
[string]$resultDirectory="..\Release\results",
[string]$appDirectory="..\Release",
[string]$appName = "Main.exe",
[string]$regex = "*.$confExtension"
)

#Write-Host $regex

$app = [io.path]::combine($appDirectory, $appName)

New-Item $resultDirectory -ItemType Directory -Force

Get-ChildItem -Path $confDirectory $regex | 
Foreach-Object {
    Write-Host "Procesing file: $_" -foregroundcolor "green"
    
    $configFile =  [io.path]::combine($confDirectory, $_.Name)
    $chartFile = [io.path]::combine($resultDirectory, $_.Name + '-chart.csv')
    $normFile = [io.path]::combine($resultDirectory, $_.Name + '-norms.csv')
    $optDeltaTFile = [io.path]::combine($resultDirectory, $_.Name + '-optDeltaT.csv')
    $args = $configFile + ' ' + $chartFile + ' ' + $normFile + ' ' + $optDeltaTFile 

    $sw = [Diagnostics.Stopwatch]::StartNew()
    $process = Start-Process -FilePath $app -ArgumentList $args -Wait -NoNewWindow #-WindowStyle Hidden
    $sw.Stop()
    Write-Host Calculated in: $sw.Elapsed -foregroundcolor "yellow"  
}