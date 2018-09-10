hello read me steps

this program is done for a Altran c++ Challenge

this repository contains c++ program in bggppchallenge.cpp file

this repository contains sample xsd.xsd filethis repository contains Dockerfile

-------------------------------------------------------------------
to sucesfully test the app you need to perform following steps

%Install docker and use only Linux images and containers within Docker

%Install the docker image available in https://hub.docker.com/_/gcc/

%open docker console 

%clone the repository to your local machine from <https://github.com/DVasyanovychAltranPT/BGCPPChallenge> from docker repository

0$ docker pull dim4ik2008/bgcppchallenge

%navigate to local folder where repository is stored <BGCPPChallenge>

0.1$ cd myFolder\BGCPPChallenge\

send following commands in docker console

1$ docker images 

%locate respective image <dim4ik2008/bgcppchallenge>

%docker run -d -it dim4ik2008/bgcppchallenge /bin/bash

4$ docker ps

%locate "dim4ik2008/bgcppchallenge" name "boring_khorana"

%enter the comand in new console prompt from "BGCPPChallenge" container

5$ docker exec -it boring_khorana /bin/bash

%compile the program

6$ g++ bgcppchallenge.cpp -o bgcppchallenge

% run the program with template.xsd parameter

7$ ./bgcppchallenge template.xsd

%after exhausting program options you can view generated files with

8.1$ cat new.xml

8.2$ cat new.json

%you can exit docker container and image with "exit" command

9$ exit 
