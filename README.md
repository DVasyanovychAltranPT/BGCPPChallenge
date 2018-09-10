hello read me steps 
this program is done for a Altran c++ Challenge
this repository contains c++ program in bggppchallenge.cpp file
this repository contains sample xsd.xsd file
this repository contains Dockerfile
-------------------------------------------------------------------
to sucesfully test the app you need to perform following steps
Install docker and use only Linux images and containers within Docker
Install the docker image available in https://hub.docker.com/_/gcc/
clone the repository to your local machine from <https://github.com/DVasyanovychAltranPT/BGCPPChallenge>
navigate to local folder where repository is stored </BGCPPChallenge>
open docker console and perform following steps
1 docker 

docker run -d -it gcc /bin/bash
4. docker ps
5. docker cp <source code file> <container>:/<source code file>
6. docker exec -it <container> /bin/bash
7. <execute steps to setup required libraries to compile and execute the program mentioned in the Readme.md>
