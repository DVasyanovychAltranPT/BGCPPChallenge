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

0$ git clone git@github.com:DVasyanovychAltranPT/BGCPPChallenge.git

%navigate to local folder where repository is stored <BGCPPChallenge>

0.1$ cd myFolder\BGCPPChallenge\

send following commands in docker console

1$ docker images 

%locate respective image <dim4ik2008/bgcppchallenge>

2$docker run -d -it gcc /bin/bash

%locate "gcc"instance name "boring_khorana"

3$ docker ps

%copy the project files bgcppchallenge.cpp and template.xsd
 
4.1$docker cp bgcppchallenge.cpp boring_khorana:/bgcppchallenge.cpp

4.2$docker cp template.xsd boring_khorana:/template.xsd

%execute docket container 

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

validate new.xml    
http://www.utilities-online.info/xsdvalidation

and new.json content      
http://www.utilities-online.info/xmltojson
