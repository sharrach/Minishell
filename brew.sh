#!/bin/sh 

 curl -L https://github.com/Homebrew/brew/archive/1.9.0.tar.gz >brew1.9.0.tar.gz 
 tar -xvzf brew1.9.0.tar.gz 
 rm -rf brew1.9.0.tar.gz 
 mv brew-1.9.0 .brew 
 rm -rf ~/goinfre/.brew 
 cp -Rf .brew ~/goinfre 
 rm -rf ./.brew 

 export PATH=$HOME/goinfre/.brew/bin:$PATH 
 export HOMEBREW_NO_AUTO_UPDATE=1
