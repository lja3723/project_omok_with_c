::::::::::::::::::::::::::::::::[readme]::::::::::::::::::::::::::::::::::::
:: [project_name]을 프로젝트 이름으로 대체하기
:: ".vs\[project_name]\v16\..."
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
rmdir /s /q "Debug"
del /s /q ".vs\바둑\v16\Browse.VC.db"
rmdir /s /q ".vs\바둑\v16\ipch\AutoPCH"