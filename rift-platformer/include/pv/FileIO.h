#ifndef _FILE_IO_H_
#define _FILE_IO_H_

#include <fstream>

namespace PV
{
	/**
	 * A file object to be used for reading from files.
	 */
	class File
	{
	public:
		/**
		 * The file constructor method.  Takes in a file name and a boolean indicating whether to load the file
		 * into memory now or later.
		 *
		 * @param fileName The name of the file to load.
		 * @param loadData True if the file's data should be loaded into memory now, false if it will be loaded manually later.
		 */
		File(const char* fileName, bool loadData);
		/**
		 * A method to load the data from the file into memory.
		 */
		void LoadData();
		/**
		 * Checks whether the file's data has been loaded into memory.
		 *
		 * @return Returns true if the file's data is loaded into memory, false otherwise.
		 */
		const bool DataLoaded() const;
		/**
		 * Gets the file's data from memory.
		 *
		 * @return The file's data from memory.
		 */
		const char* Data() const;
		/**
		 * Gets the size of the file's data.
		 *
		 * @return Returns the size of the file if it is loaded, returns 0 otherwise.
		 */
		const unsigned long Size() const;
		/**
		* A pointer to the file's data in memory.
		*/
		char* data;
		/**
		 * Free's the file's data from memory.  The file can than be reloaded with the LoadData method later.
		 */
		void FreeData();
		/**
		 * The deconstructor for the file.  This will remove all of the file's properties.
		 */
		~File();
	protected:
		/**
		 * The file's input stream for retrieving its data.
		 */
		FILE* file;
		/**
		 * A boolean indicating whether the file is loaded or not.
		 */
		bool dataLoaded;
		/**
		 * The size of the file's data in memory.
		 */
		unsigned long fileLength;
		/**
		 * A protected method for closing the file.  Only called in the deconstructor.
		 */
		void Close();
	};
};

#endif

