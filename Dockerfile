    FROM gcc:5.5
    COPY . /BGCPPChallenge
    WORKDIR /BGCPPChallenge
    RUN g++ -o BGCPPChallenge bgcppchallenge.cpp
    CMD ["./BGCPPChallenge"]
	