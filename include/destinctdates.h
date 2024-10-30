// 

//will have data set with temperatures at 6 or 7 am for the dates
// 3rd of april, 26th of june, 29th of september and 24th of december between 1850 and 2023

//whant to sort the data so that it takes out all the things for different years
//four plots in one, with years on the x-axis, and the temperature on the y-axis


//whant a list? of all the temperatures for all the dates seperatally. should be the same size
// 24th of december will be missing from 2023 start with the other three

//make a function that takes the data and separetes them into the different dates 
//1 "list/array/vector with the years should have the size 139 
// for the 3rd: picks out all the temeratures for the 3rd should also have size of 139


// data i want start at line 8
// column 1: datum 0000-00-00 
// column 2: tid  00:07:00
// column 3: lufttemperatur 0.0

// whant to remove the column with the time since its not important to the analazys, and heith above sea level

#ifndef DESTINCT
#define DESTINCT
#include <string>

int getFourDates(const std::string filename);


#endif





  