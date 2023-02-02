
cmake_minimum_required(VERSION 3.14)
project(lipkep)

set(CMAKE_CXX_STANDARD 14)

#------------------- CREATION DES VARIABLES POUR LA BIBLIOTHEQUE GUROBI -----------------------
message(STATUS "CMAKE_SYSTEM_NAME : ${CMAKE_SYSTEM_NAME}")
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux") #Pour Linux
	set(GUROBI_ROOT "/opt/gurobi1000/linux64") #A Modifier si votre chemin est différent
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows") #Pour Windows
	set(GUROBI_ROOT "C:/gurobi952/win64") #A Modifier si votre chemin est différent
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin") #Pour MacOS
	set(GUROBI_ROOT "/Library/gurobi952/mac64") #A Modifier si votre chemin est différent
endif()



message(STATUS "GUROBI_ROOT : ${GUROBI_ROOT}")

# On créé une variable stockant le dossier où se situent les fichiers en-tête du solveur GUROBI (pour la compilation)
set(GUROBI_INCLUDE_DIR "${GUROBI_ROOT}/include")
message(STATUS "GUROBI_INCLUDE_DIR : ${GUROBI_INCLUDE_DIR}") #On affiche le dossier précédent (pour DEBUG)

# On créé des variables stockant l'emplacement des biblothèques/librairies du solveur GUROBI (pour l'édition des liens)
# ATTENTION -> Selon la version utilisée, il faut modifier le nom de la librairie ci-dessous
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux") #Pour Linux
	set(GUROBI_LIBRARY_1 "${GUROBI_ROOT}/lib/libgurobi_c++.a")
	set(GUROBI_LIBRARY_2 "${GUROBI_ROOT}/lib/libgurobi100.so")
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows") #Pour Windows
	set(GUROBI_LIBRARY_1 "${GUROBI_ROOT}/lib/gurobi100.lib")
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    	set(GUROBI_LIBRARY_2 "${GUROBI_ROOT}/lib/gurobi_c++mdd2019.lib")
	else()
    	set(GUROBI_LIBRARY_2 "${GUROBI_ROOT}/lib/gurobi_c++md2019.lib")
	endif()
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin") #Pour MacOS
	set(GUROBI_LIBRARY_1 "${GUROBI_ROOT}/lib/libgurobi_c++.a")
	set(GUROBI_LIBRARY_2 "${GUROBI_ROOT}/lib/libgurobi91.dylib")
endif()
set(GUROBI_LIBRARIES ${GUROBI_LIBRARY_1} ${GUROBI_LIBRARY_2})
message(STATUS "GUROBI_LIBRARIES : ${GUROBI_LIBRARIES}") #On affiche les chemins vers les biblothèques (pour DEBUG)

#------------------- PARTIE PRINCIPALE -----------------------
# On indique où trouver les définitions des fonctions du solveur GUROBI
include_directories(${GUROBI_INCLUDE_DIR})
include_directories(include)

# Définition des fichiers sources à utiliser
file(GLOB_RECURSE p1 ../../src/common/*.cpp)
file(GLOB_RECURSE p2 ../../src/lip/*.cpp)
set(SRCS ${p1} ${p2})

message(STATUS "SRCS : ${SRCS}") #Affiche tous les fichiers cpp trouvés (pour DEBUG)

# On indique que l'on veut un exécutable "keplip" compilé à partir des fichiers stockés dans SRCS
add_executable(lipkep.exe ${SRCS})

# On indique où trouver les biblothèques du solveur GUROBI
target_link_libraries(lipkep.exe ${GUROBI_LIBRARIES})

# On ajoute un lien symbolique vers le dossier data dans le dossier où se situera l'exécutable
# (cela permet d'indiquer le chemin d'une instance contenu dans le dossier data en indiquant simplement un chemin relatif et non absolu)
if (UNIX)  #Pour MacOS et Linux
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/../../data ${CMAKE_CURRENT_BINARY_DIR}/data)
else()  #Pour Windows
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/data" _dstDir)
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/data/" _srcDir)
    execute_process(COMMAND cmd.exe /c mklink /J "${_dstDir}" "${_srcDir}")
endif()
