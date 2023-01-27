// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r"); // cria o input e abre como sendo o arquivo inicial e aplica "r" porque só vai ser lido;
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w"); // cria o output e abre como sendo o arquivo final e aplica "w" porque vai ser escrito nele;
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; // cria um espaço na memória do computador pra salvar o header do arquivo 'wav';
    fread(header, HEADER_SIZE, 1, input); // lê os 44bytes do HEADER_SIZE do arquivo input e salva na array criada 'header';
    fwrite(header, HEADER_SIZE, 1, output); // cola/escreve o que estava salvo na array header, de tamanho HEADER_SIZE, no arquivo output;

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input)) // ler 1 sample de 16 bits cada - 2bytes -  do arquivo input para o endereço do 'buffer';
    {
        // Update Volume:
        buffer *= factor; // pra cada sample lido e salvado em 'buffer', atualize multiplicando cada um por 'factor';
        fwrite(&buffer, sizeof(int16_t), 1, output); // escreva o que está em '&buffer', para o arquivo 'output' como tamanho de int16_t;
    }

    // Close files
    fclose(input);
    fclose(output);
}
