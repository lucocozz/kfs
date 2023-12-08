FROM debian:buster

RUN apt update \
	&& apt install -y build-essential \
		grub-pc-bin xorriso bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo wget nasm gcc-multilib grub-common

RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz \
&&  tar -xzvf binutils-2.39.tar.gz \
&&  mkdir build-binutils \
&&  cd build-binutils \
&&  ../binutils-2.39/configure --target=i686-elf --prefix=/usr/local \
&&  make \
&&  make install \
&&  cd ..

RUN wget https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz \
&& tar -xzvf gcc-12.2.0.tar.gz \
&& mkdir build-gcc \
&& cd build-gcc \
&& ../gcc-12.2.0/configure --target=i686-elf --prefix=/usr/local --disable-nls --enable-languages=c \
&& make all-gcc \
&& make all-target-libgcc \
&& make install-gcc \
&& make install-target-libgcc \
&& cd ..

# install meson
RUN apt-get install -y meson

RUN mkdir kfs

WORKDIR /kfs

CMD ["tail", "-f", "/dev/null"]
