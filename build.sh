ROOT_DIR=`pwd`

printf "${CYAN}4. Main software...${NC}\n"
cd $ROOT_DIR
mkdir -p build && cd build
cmake $ROOT_DIR/software/libcariboulite/
make
sudo make install
sudo ldconfig
