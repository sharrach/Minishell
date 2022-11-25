#!/bin/sh  

 echo "installing brew..."  
 sh ~/brew.sh > /dev/null 2>&1 
 brew upgrade > /dev/null 2>&1 
 brew update > /dev/null 2>&1 

 echo "done." 

 echo "installing readline..." 
 echo "it might take a few minutes." 
 brew install readline > /dev/null 2>&1 
 echo "done."
