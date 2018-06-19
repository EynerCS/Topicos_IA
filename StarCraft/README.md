1) Primer paso: Instalación
   - Instalar Visual Studio 2013
   - Instalar StarCraft: Brood War
   - Hacer un update StarCraft: Brood War a 1.16.1
   - Instalar BWAPI

2) Paso dos: Compilar
   - Abrir ExampleProjects.sln en el directorio de instalación BWAPI
   - Crear el proyecto ExampleAIModule en modo RELEASE
   - Copiar ExampleAIModule.dll a bwapi-data / AI dentro de la carpeta de instalación de StarCraft
   
3) Paso tres: Ejecutar StarCraft a través de Chaoslauncher
   - Ejecutar Chaoslauncher.exe como administrador
   - Chaoslauncher se encuentra en el directorio Chaoslauncher del directorio de instalación de BWAPI
   - Verificar el injector BWAPI x.x.x [RELEASE]
   - Click en Start
     (Asegúrar de que la versión esté configurada en Starcraft 1.16.1, no en ICCup 1.16.1)

4) Paso cuatro: Correr el juego contra la IA
   - Ir a Single Player -> Expansion
   - Seleccionar cualquier usuario y dar click OK
   - Click Play Custom, seleccionar un mapa, y empezar el juego

5) Paso cinco: Correr el juego contra uno mismo
   - Correr Chaoslauncher - MultiInstance.exe como administrador
   - Start
     . Ir a Multiplayer -> Expansion -> Local PC
     . Seleccionar cualquier usuario y click OK
     . Click Create Game, seleccionar un mapa, y click OK
   - Start -- Uncheck BWAPI Injector x.x.x [RELEASE] para permitir un juego consigo mismo, dejar a la maquina jugar
     . Ir a Multiplayer -> Expansion -> Local PC
     . Seleccionar cualquier usuario y dar click OK
     . Unir el juego existente creado por el otro cliente.
     
REFERENCIAS

http://bwapi.github.io/
https://github.com/bwapi/bwapi/issues
https://github.com/bwapi/bwapi/releases
https://github.com/bwapi/bwapi/wiki/Useful-Links
