FROM debian:buster

RUN apt update \
	&& apt install -y build-essential \
		grub-pc-bin xorriso bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo wget nasm gcc-multilib grub-common make

# install meson
RUN apt-get install -y meson

RUN mkdir kfs

WORKDIR /kfs

CMD ["make", "all"]
