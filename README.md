# MNXB11-final-project

## Libraries used
- ROOT
- Vince's CSV Parser 

## How to use the code

The program uses 3 header and corresponding .cxx files, each corresponding to a different type of data. As pre-processing, the program utilizes a bash script that creates files in a format specific to each type of data. The ROOT is implemented within each header file. As such, the main function in main.cxx only uses the functions from the headers and returns appropriate plots. 
The CSV files are parsed accordingly within the respective header files using Vince's CSV Parser library and some of the standard libraries.

NOTE: YOU NEED TO BE IN THE COURSE CONTAINER FOR ROOT TO WORK
To run the program, first you need to run make from the root directory. Then, after compilation is finished, you will be able to run ./main. Upon executing this command you will be prompted to provide a filepath to a CSV file. You can provide an absolute path or a relative path to the root folder. The format of the data in the CSV file has to be "YYYY-MM-DD;something;TEMPERATURE". Afterwards, you will be asked to choose one of the three modes: coldwarm, 4dates, and winter. Each of these corresponds to a type of data: 
- coldwarm - coldest and warmest temperatures of each year,
- 4dates - the temperatures on 03 April, 26 June, 29 September, and 24 December,
- winter - average temperatures of winter (November - February) for each year.

You will also be able to type "exit" which will close the program. The program will also terminate if an invalid filepath is provided.
After execution, you will be presented with a graph (histograms for cold/warm and 4 dates, a line graph with a linear fit for average winter temperatures). To close the graph and terminate the application, you must press enter in the CLI. The graphs generated will be in the root folder along with the CSV files created by the pre-processing bash script.

## How the code works
Each header file includes a main function that both parses the CSV files and plots the data using helper functions also defined in said header file. The parsing functions utilize Vince's CSV Parser library to parse through the CSV files in order to extract the dates and temperatures from the dataset. The years are extracted from the dates. These functions are initialized with the filename string, and vectors of ints and doubles (int for year, double for temperature). They fill those vectors using the data extracted from the file given by filename. The plotting functions use the ROOT library to take vectors and plot them. The main function is initialized with just the filepath, which it converts to an appropriate filename which corresponds to a pre-processed dataset in the root folder. Then it initializes vectors needed for plotting, and fills them using the parsing function. Finally, it plots them using the plotting function.
The main.cxx code has a main function that is initialized with nothing but asks to provide a filepath. That filepath is checked for validity using a helper function. If it is invalid the program terminates. If it is valid, the user is then prompted to provide a mode or type exit to close the program. If provided an invalid mode, which is checked using another helper function, the user is prompted again to provide a valid mode or type exit to close the program. If the mode is valid, the main function then executes the respective main function from the appropriate header file which displays the graph, and the user is told to press Enter in order to close the application. After pressing Enter the ROOT application terminates, closing the graph and closing the program. The generated graphs are saved as .png files in the root folder.
