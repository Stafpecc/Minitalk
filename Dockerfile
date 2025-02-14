FROM debian:latest
RUN apt-get update && apt-get install -y gcc make
COPY . /minitalk
WORKDIR /minitalk
RUN make
CMD ["./server"]
