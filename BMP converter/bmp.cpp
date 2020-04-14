
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void main()
{
	string sFileName;
	BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    int Width, Height;
	int const colors = 256;
	RGBQUAD Palette[colors];
    RGBTRIPLE *inBuf;
    BYTE *outBuf;
    HANDLE hInputFile, hOutFile;
    DWORD RW;

	cout << "Enter the full name, please: ";
	cin >> sFileName;

	hInputFile = CreateFile(sFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hInputFile == INVALID_HANDLE_VALUE)
		return;

	hOutFile = CreateFile("Result.bmp", GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
    if (hOutFile == INVALID_HANDLE_VALUE)
    {
		CloseHandle (hInputFile);
		return;
	}
	
	// Считываем инфу
    ReadFile (hInputFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW, NULL);
    ReadFile (hInputFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW, NULL);

	// Установим указатель на начало растра
    SetFilePointer (hInputFile, bmpFileHeader.bfOffBits, NULL, FILE_BEGIN);
    Width = bmpInfoHeader.biWidth;
    Height = bmpInfoHeader.biHeight;

	// Выделим память
    inBuf = new RGBTRIPLE [Width];
    outBuf = new BYTE [Width * 2];

	// Заполним заголовки
    bmpFileHeader.bfOffBits = sizeof (bmpFileHeader) + sizeof (bmpInfoHeader) + 1024;                              
	bmpInfoHeader.biBitCount = 16;
    bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + Width * Height + Height * (3*Width % 4);   

	// Запишем заголовки
    WriteFile (hOutFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW, NULL);
    WriteFile (hOutFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW, NULL);
	// Палитра черно-белая
	for (int i = 0; i < colors; i++)
	{
		Palette[i].rgbBlue = i;
		Palette[i].rgbGreen = i;
		Palette[i].rgbRed = i;
	}
	WriteFile (hOutFile, Palette, colors * sizeof (RGBQUAD), &RW, NULL);

	// Начнем преобразовывать
    for (int i = 0; i < Height; i++)
    {
        ReadFile (hInputFile, inBuf, sizeof(RGBTRIPLE) * Width, &RW, NULL);
		for (int j = 0; j < Width * 2; j+=2)
		{
			//outBuf[j + 1] = (inBuf[j / 2].rgbtRed & 0xF8) | (inBuf[j / 2].rgbtGreen >> 5);
			//outBuf[j] = ((inBuf[j / 2].rgbtGreen << 3) & 0xE0) | (inBuf[j / 2].rgbtBlue >> 3);

			//outBuf[j + 1] = (inBuf[j / 2].rgbtRed >> 1 & 0xFC) | (inBuf[j / 2].rgbtGreen >> 6);
			//outBuf[j] = (inBuf[j / 2].rgbtGreen >> 3 << 5) | (inBuf[j / 2].rgbtBlue >> 3);

			outBuf[j + 1]	= ((inBuf[j / 2].rgbtRed / 8) >> 10) + ((inBuf[j / 2].rgbtGreen / 8) >> 5);
			outBuf[j]		= ((inBuf[j / 2].rgbtGreen / 8) >> 5) + ((inBuf[j / 2].rgbtBlue / 8));
		}

        WriteFile (hOutFile, outBuf, 2 * sizeof(BYTE) * Width, &RW, NULL);

		// Пишем мусор для выравнивания
        WriteFile (hOutFile, Palette, (3 * Width) % 4, &RW, NULL);
        SetFilePointer (hInputFile, Width % 4, NULL, FILE_CURRENT);
    }

    delete[] inBuf;
    delete[] outBuf;
    CloseHandle (hInputFile);
    CloseHandle (hOutFile);

	cout << "Updating has come to the end successfully!";
	system("pause");
}