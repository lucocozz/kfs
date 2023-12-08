FROM debian:buster

RUN apt update \
	&& apt install -y build-essential \
		grub-pc-bin xorriso libgmp3-dev libmpc-dev \
		libmpfr-dev texinfo nasm gcc grub-common \
		make python3-pip ninja-build

RUN mkdir kfs
RUN pip3 install meson

WORKDIR /kfs

CMD ["make"]
