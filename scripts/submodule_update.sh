#!/bin/bash

git submodule foreach --recursive '
    cd $toplevel/$name    
    git checkout $(git config -f $toplevel/.gitmodules submodule.$name.branch || echo master)
    git pull origin $(git rev-parse --abbrev-ref HEAD)
    cd -
'

git add .gitmodules $(git submodule foreach --quiet --recursive pwd)
git commit -m "Update submodules to their respective latest branches"


# git push origin main