# GrafikaProjekt

## Instalacja: 

Oprogramowanie i biblioteki:
  - SFML wersja 2.4.1 (pobrana i wypakowana np: do folderu C:\SFML-2.4.1) http://www.sfml-dev.org/files/SFML-2.4.1-windows-vc14-32-bit.zip
  - Microsoft Visual Studio Community 2015
  
Link do tutoriala na podstawie którego zainicjalizowano projekt:
  - http://www.sfml-dev.org/tutorials/2.4/start-vc.php

Zmiany w ustawieniach projektu:
### Debug: 

C/C++ Preprocessor/General/Additional Include Directories:
```
C:\SFML-2.4.1\include;%(AdditionalIncludeDirectories)
```

C/C++ Preprocessor/Preprocessor Definitions:
```
SFML_STATIC ;WIN32;_DEBUG;_WINDOWS;%(PreprocessorDefinitions)
```

Linker/General/Additional Library Directiories:
```
C:\SFML-2.4.1\lib;%(AdditionalLibraryDirectories)
```

Linker/Input/Additional Dependencies:
```
sfml-graphics-s-d.lib;sfml-window-s-d.lib;sfml-system-s-d.lib;sfml-audio-s-d.lib;sfml-main-d.lib;opengl32.lib;freetype.lib;jpeg.lib;winmm.lib;gdi32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;%(AdditionalDependencies)
```

## Release
C/C++ Preprocessor/General/Additional Include Directories:
```
C:\SFML-2.4.1\include;%(AdditionalIncludeDirectories)
```

C/C++ Preprocessor/Preprocessor Definitions:
```
SFML_STATIC ;WIN32;_DEBUG;_WINDOWS;%(PreprocessorDefinitions)
```

Linker/General/Additional Library Directiories:
```
C:\SFML-2.4.1\lib;%(AdditionalLibraryDirectories)
```

Linker/Input/Additional Dependencies:
```
sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;sfml-audio-s.lib;sfml-main.lib;opengl32.lib;freetype.lib;jpeg.lib;winmm.lib;gdi32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;%(AdditionalDependencies)
```
