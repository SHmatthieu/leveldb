# levelDB en WebAssembly

# Guide d'installation

Ce guide reviens sur les differentes étapes pour compiler et éxecuter levelDB en WebAssembly pour wasm-micro-runtime.
Il est important de noter qu'il n'est pas obligatoire de mettre en place le compilateur (ce qui peu etre un peu long) pour tester les exemples (/exemple_wasm), il suffit d'installer le runtime (wasm-micro-runtime) ce qui est plutot rapide.

## installation du runtime (wamr)

le github de wamr propose un guide d'installation complet en fonction de la platforme.
Attention il faut obligatoirement activer le support de pthread ce qui n'est pas par défault (-DWAMR_BUILD_LIB_PTHREAD=1 en paramètre cmake).
https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/build_wamr.md#linux

### jit

Pour tester en mode jit il faut recompiler wamr mais il faut aussi compiler llvm ce qui est assez long (ne pas oublier pthread) mais tout est détaillé sur leur github.

### aot

Pour utiliser le mode aot il n'y a pas besoin de recompiler le runtime mais il faut compiler wamrc pour convertir un fichier wasm en fichier aot.
https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/README.md#build-wamrc-aot-compiler

```
wamrc -o <AOT file> <WASM file>
iwasm <AOT file>
```

### exemple

commande utilisé pour installer wamr sur ma machine (ubuntu 20.04)
(similaire au guilde d'installation wamr sur linux):

```
git clone https://github.com/bytecodealliance/wasm-micro-runtime.git
sudo apt install build-essential cmake g++-multilib libgcc-8-dev lib32gcc-8-dev
cd wasm-micro-runtime/product-mini/platforms/linux/
mkdir build && cd build
cmake -DWAMR_BUILD_LIB_PTHREAD=1 ..
make
```

si ca a marché alors il y a maintenant un executable iwasm qui correspond au runtime.

### utiliser iwasm

Maintenant que iwasm est installé on peu executer les fichiers bytecode WebAssembly (different exemple dans /exemple_wasm)

```
./iwasm exemple.out
```

pour pouvoir utiliser levelDB en wasm il est important de donner l'accès au dossier dans lequel le programme ecrira la base de donnée.

```
./iwasm --dir=. a.out
```

### tips

J'ai ajouté un alias iwasm vers l'endroit ou j'ai installé iwasm dans mon fichier .bashrc (.zshrc dans mon cas) pour pouvoir utiliser facilement iwasm.

```
alias iwasm="/install-path/wasm-micro-runtime/product-mini/platforms/linux/build/iwasm"

```

## Compilateur

Pour pouvoir compiler levelDB vers WebAssemlby il faut installer wasi-sdk et y apporter quelques modification. (il n'est pas nécessaire d'avoir le compilateur pour tester levelDB en wasm, le projet est déjà compilé dans /exemple_wasm)

### set up le compilateur

[wasi sdk
](https://github.com/WebAssembly/wasi-sdk)
des versions déjà compilé de wasi sdk sont présent sur leur github (j'ai utilisé la version 15).
sinon il est possible de compiler directement avec cmake

j'ai ajouter un variable WASI_SDK_PATH pour pouvoir l'utilser plus facilement

```
export WASI_SDK_PATH="/path/wasi-sdk-15.0"
```

https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/pthread_library.md

Pour pouvoir utiliser pthread avec wasi_sdk il faut ajouter pthread.h au sysroot

```
cp ${WAMR_ROOT}/wamr-sdk/app/libc-builtin-sysroot/include/pthread.h /opt/wasi-sdk/share/wasi-sysroot/include
```

### compiler levelDB

levelDB ce compile via cmake cependant il faut quand même passer quelque arguments à cmake avant de lancer.

-   WASI_SDK_PREFIX=path vers wasi sdk
-   MAKE_TOOLCHAIN_FILE=path vers le fichier de configuration cmake pour wasi-sdk
-   CMAKE_SYSROOT=path vers le sysroot de wasi-sdk
-   CMAKE_BUILD_TYPE=Release

```
rm -fr build && mkdir build && cd build
cmake -DWASI_SDK_PREFIX=$WASI_SDK_PATH -DCMAKE_TOOLCHAIN_FILE=$WASI_SDK_PATH/share/cmake/wasi-sdk.cmake -DCMAKE_SYSROOT=$WASI_SDK_PATH/share/wasi-sysroot -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..
```

un scipt bash (compile.sh) pour compiler le projet est présent à la racine du projet (il faut la varaible $WASI_SDK_PATH).

### compiler les exemples

differents code source d'exemple et de benchark sont présent dans le dossier /mytest. Compiler un exemple qui utilise levelDB peut etre un petit peu complexe (car il y a beaucoup de flag nécessaire) heureusment un makefile est présent.

```
make       #exemple simple
make write #exempe d'ecriture
make read  #exemple de lecture
make bench #benchmarks

iwasm --dir=. a.out #pour lancer l'exemple qui vient d'etre compilé
```

### compiler un nouveau programme qui utilise levelDB

le meilleur moyen pour utiliser levelDB en WebAssembly dans un nouveau programme est de regarder comment sont compiler les exemples dans le makefile dans /mytest. (il faut au préalable avoir compilé levelDB)

## Arborescence du projet

le projet est un fork de levelDB la structure est donc similaire.

-   /util tout les fichers contenant le wasi dans le nom on été rajouté
-   /port port_wasi.h à été rajoué et port.h modifé
-   /exemple_wasm contient des exemples déjà compilé
-   /mytest contient le code source des exemple et un makefile pour les compiler
-   le script compile.sh permet de compiler facilement le projet sous linux dans le dossier build.
