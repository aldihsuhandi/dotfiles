#ifndef _IOSTREAM_
#include <iostream>
#define _IOSTREAM_
#endif

#ifndef _STRING_
#include <string>
#define _STRING_
#endif

#ifndef _VECTOR_
#include <vector>
#define _VECTOR_
#endif

#include <random>

class EncodeDecode
{
public:
    EncodeDecode()
    {
        get_config_file_loc();
        FILE *secret_file = fopen(this->secret_key_file.c_str(), "r");
        if (secret_file != NULL)
        {
            read_secret_file(secret_file);
            fclose(secret_file);
        }
        else
        {
            this->secret = generate_secret();
            secret_file = fopen(this->secret_key_file.c_str(), "w");
            fprintf(secret_file, "%s\n", this->secret.c_str());
            fclose(secret_file);
        }

        calculate_modifier();
    }

    std::string decode(std::string encoded_string)
    {
        std::string decoded;
        for (int i = 0; i < (int)encoded_string.length(); ++i)
        {
            decoded += ((encoded_string[i] ^ this->secret[fast_gcd(i + 1, this->modifier) % this->secret.length()]) % 95) + 32;
        }
        return decoded;
    }

    std::string encode(std::string str)
    {
        std::string encrypted;
        for (int i = 0; i < (int)str.length(); ++i)
        {
            encrypted += ((str[i] ^ this->secret[fast_gcd(i + 1, this->modifier) % this->secret.length()]) % 95) + 32;
        }
        return encrypted;
    }

private:
    std::string secret_key_file;
    std::string secret;
    int modifier;

    std::string generate_secret()
    {
        const std::string alphabet = "abcdefghijklmnopqrstuvwxyz0123456789";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

        std::string secret;
        for (int i = 0; i < 512; ++i)
        {
            secret += alphabet[dis(gen)];
        }

        return secret;
    }

    void calculate_modifier()
    {
        int t_modifier = 1;
        int secret_length = this->secret.length();
        for(char c: this->secret) 
        {
            t_modifier = fast_lcm(t_modifier, (long) c) % secret_length;
        }

        this->modifier = t_modifier;
    }

    void get_config_file_loc()
    {
        char file_dir[1024];
        FILE *file = popen("echo $HOME", "r");
        fscanf(file, "%[^\n]\n", file_dir);
        fclose(file);

        this->secret_key_file = (std::string)file_dir + "/.config/wm script/network-select/key.secret";
    }

    void read_secret_file(FILE *secret_file)
    {
        char buffer[1024];
        fscanf(secret_file, "%[^\n]\n", buffer);
        this->secret = (std::string)buffer;
    }

    long fast_gcd(long a, long b) 
    {
        while (b != 0) 
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    long fast_lcm(long a, long b) {
        return std::abs(a * b) / fast_gcd(a, b);
    }
};
