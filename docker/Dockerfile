# Start from the ubuntu image
FROM ubuntu:focal AS build

# Avoid interactive menus when installing dependencies
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt-get -y upgrade
RUN apt -y install build-essential 
RUN apt -y install cmake
RUN apt -y install git

# Define working directory for build stage
WORKDIR /var/www/html

# Install repository
RUN git clone https://github.com/vuola/UH_NumericalMethods.git /var/www/html/UH_NumericalMethods

# Install dev environment
RUN apt -y install python3
RUN apt -y install curl
RUN curl -o eigen-3.4.0.tar.bz2 https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.bz2
RUN tar -xvjf eigen-3.4.0.tar.bz2 -C /var/www/html
RUN mkdir eigen3
RUN cd eigen3
RUN cmake /var/www/html/eigen-3.4.0
RUN apt -y install libboost-all-dev
RUN echo "deb [arch=amd64] http://robotpkg.openrobots.org/packages/debian/pub focal robotpkg" >> /etc/apt/sources.list.d/robotpkg.list
RUN curl http://robotpkg.openrobots.org/packages/debian/robotpkg.key | apt-key add -
RUN apt-get update
RUN apt -y install robotpkg-py38-eigenpy

# build
RUN cmake -S /var/www/html/UH_NumericalMethods -B /var/www/html/UH_NumericalMethods/build
RUN cmake --build /var/www/html/UH_NumericalMethods/build

RUN rm -R /var/www/html/UH_NumericalMethods/build/exercise*/CMakeFiles
RUN rm -R /var/www/html/UH_NumericalMethods/build/exercise*/*.cmake
RUN rm -R /var/www/html/UH_NumericalMethods/build/exercise*/Makefile

# Final container
FROM ubuntu:focal AS final

# Install python to the final container
RUN apt update
RUN apt -y install python3

# Copy compiled artifacts from the build container
COPY --from=build /var/www/html/UH_NumericalMethods/build/exercise*/* /app/executables/
COPY --from=build /var/www/html/UH_NumericalMethods/build/exercise*/*.so /app/executables/
COPY --from=build /var/www/html/UH_NumericalMethods/build/exercise*/*.py /app/executables/

# Set the working directory
WORKDIR /app/executables

# Specify the command to run when the final container starts
CMD ["sh"]