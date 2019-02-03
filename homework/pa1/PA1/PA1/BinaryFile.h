#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include <vector>
#include <string>

using namespace std;
class BinaryFile
{
public:

	//writes a vector of strings to a file.  Assumes each character in each string is either a 0 or 1
	static void writeToFile(const vector<bool> &content, const string &output_file_name)
	{
		//open file in binary mode
		ofstream output_file{ output_file_name, ofstream::binary };

		//keeps track of all of the chars that we will write to file
		vector<char> to_output{};

		//convert strings into vector of chars
		char buffer = (char)0;
		int buffer_counter = 0;
		for (bool item : content)
		{
			//bit shift all characters in string into single character

			if (buffer_counter == 8 * sizeof(char))
			{
				//char full, save to vector
				to_output.push_back(buffer);
				buffer = (char)0;
				buffer_counter = 0;
			}
			buffer = buffer << 1;
			if (item == true)
			{
				buffer = buffer | 1;
			}
			buffer_counter++;
		}

		//account for any leftover buffer
		if (buffer_counter > 0)
		{
			while (buffer_counter < 8)
			{
				buffer = buffer << 1;
				buffer_counter++;
			}
			to_output.push_back(buffer);
		}

		//finally, write to file
		//first entry indicates number of bits that are contained within the file
		size_t num_bits = content.size();
		output_file.write((char *)&num_bits, sizeof(size_t));

		//now, write binary contents
		for (char item : to_output)
		{
			output_file.write(&item, sizeof(char));
		}
		output_file.close();
	}

	//reads a file written with writeToFile into a vector of bools
	static vector<bool> readFromFile(const string &input_file_name)
	{
		vector<bool> result{};
		ifstream input_file{ input_file_name, ofstream::binary };

		//pick off number of bits to read
		size_t bits_to_read = 0;
		input_file.read((char *)&bits_to_read, sizeof(size_t));

		//now, pull in single chars
		char single_char = '\0';
		size_t bits_read = 0;
		for (int i = 0; i < bits_to_read; i += 8 * sizeof(char))
		{
			input_file.read(&single_char, sizeof(char));
			for (int j = 0; j < 8 * sizeof(char) && bits_read < bits_to_read; j++)
			{
				//peel off one char, then shift to get the next one for the loop
				char bool_val = single_char >> 8 * sizeof(char);
				bool_val = bool_val & 1;
				result.push_back((bool)bool_val);
				single_char = single_char << 1;
				bits_read++;
			}
		}

		//close file
		input_file.close();

		//finally, return result vector
		return result;
	}
};

#endif
