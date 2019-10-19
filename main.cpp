#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
	std::string folder_path = "C:\\Folder";

	int oneClusterSize = 0; // bytes

	char* pszDrive = NULL;
	DWORD dwSectPerClust = 0;
	DWORD dwBytesPerSect = 0;
	DWORD dwFreeClusters = 0;
	DWORD dwTotalClusters = 0;

	GetDiskFreeSpace(pszDrive, &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	oneClusterSize = dwSectPerClust * dwBytesPerSect;

	for (const auto& file : fs::directory_iterator(folder_path))
	{
		int fileSize = fs::file_size(file.path());
		int clustersCount = (fileSize / oneClusterSize) ? (fileSize / oneClusterSize): 1;

		std::cout << file.path() << "file size " << fileSize << " bytes, "
			<< "file clusters " << ceil(clustersCount) << std::endl;
	}
	
	getchar();
	return 0;
}