#include <iostream>
#include <gdal.h>

int main() {
    GDALAllRegister();

    std::cout << "GDAL connected successfully!" << std::endl;
    std::cout << "GDAL Version: "
              << GDALVersionInfo("RELEASE_NAME") << std::endl;

    return 0;
}
