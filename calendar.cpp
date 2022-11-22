/***************************
 * Автор: Вяткин Владислав *
 * Группа: ПИ-221          *
 * Название: Календарь     *
 * Дата: 21.11.2022        *
 ***************************/

#include <iostream>
#include <cmath>

using namespace std;

const int dayOfWeekCount = 6;
  
string dayOfWeek[dayOfWeekCount] = { "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ" };

const int monthsCount = 12;

struct month {
  string monthsNames[monthsCount] = { "ЯНВАРЬ", "ФЕВРАЛЬ",
                                     "МАРТ", "АПРЕЛЬ", "МАЙ",
                                     "ИЮНЬ", "ИЮЛЬ", "АВГУСТ",
                                     "СЕНТЯБРЬ", "ОКТЯБРЬ", "НОЯБРЬ",
                                     "ДЕКАБРЬ" };

  int dayOfMonthCount[monthsCount] = { 31, 28,
                                       31, 30, 31,
                                       30, 31, 31,
                                       30, 31, 30,
                                       31 };
                                       
  int monthLeapIndex = 1;
} months;

void Week() { // отрисовка плашки с днями недели
  for (int dayIndex = 0; dayIndex < dayOfWeekCount; ++dayIndex) {
    cout << dayOfWeek[dayIndex] << "\t";
  }
}

void Month(int monthIndex, int& dayOfWeekOfFirstDayOfMonth, int& dayOfWeekOfFirstDayOfMonth2) { // отрисовка месяца календаря
  
  cout << "\t\t\t\t" << months.monthsNames[monthIndex]
       << "\t\t\t\t\t\t    " << months.monthsNames[monthIndex + monthsCount / 2] << "\n\n";
  
  cout << "\t";
  Week();
  cout << "\t";
  Week();
  cout << endl;
  
  if (monthIndex == 0) {
    for (int monthIndex2 = 0; monthIndex2 < (monthsCount / 2); ++monthIndex2) {
      for (int dayIndex = 0; dayIndex < months.dayOfMonthCount[monthIndex2]; ++dayIndex) {
        if (dayOfWeekOfFirstDayOfMonth2 == dayOfWeekCount + 1) {
          dayOfWeekOfFirstDayOfMonth2 = 1;
        }
        
        ++dayOfWeekOfFirstDayOfMonth2;
      }
      
      --dayOfWeekOfFirstDayOfMonth2;
      
      if (dayOfWeekOfFirstDayOfMonth2 == dayOfWeekCount) {
        dayOfWeekOfFirstDayOfMonth2 = 1;
      } else {
        ++dayOfWeekOfFirstDayOfMonth2;
      }
    }
  }
  
  int dayVoid1 = dayOfWeekOfFirstDayOfMonth  - 1,
      dayVoid2 = dayOfWeekOfFirstDayOfMonth2 - 1;
  
  for (int dayOfWeekIndex = 0; dayOfWeekIndex < dayVoid1; ++dayOfWeekIndex) {
    cout << "\t" << " ";
  }
  
  int dayIndex1 = 0, dayIndex2 = 0;
  bool flag = false;
  while (dayIndex1 != months.dayOfMonthCount[monthIndex] || dayIndex2 != months.dayOfMonthCount[monthIndex + 6]) {
    for (int index = 0; index < (dayOfWeekCount - dayVoid1); ++index) {
      if (dayIndex1 == months.dayOfMonthCount[monthIndex] && flag == false) {
        for (int dayOfWeekIndex = 0; dayOfWeekIndex < dayOfWeekCount - dayOfWeekOfFirstDayOfMonth;
         ++dayOfWeekIndex) {
          cout << "\t" << " ";
          flag = true;
        }
        cout << "\t";
        break;
      } else if (flag == true) {
        for (int dayOfWeekIndex = 0; dayOfWeekIndex < dayOfWeekCount; ++dayOfWeekIndex) {
          cout << "\t" << " "; 
        }
        break;
      } else {
        cout << "\t" << dayIndex1 + 1;
        ++dayIndex1;
        ++dayOfWeekOfFirstDayOfMonth;
        if (dayOfWeekOfFirstDayOfMonth == dayOfWeekCount + 1) {
          dayOfWeekOfFirstDayOfMonth = 1;
        }
      }
    }
    
    
    if (dayVoid2 == 0) {
      cout << "\t";
    } else {
      cout << "\t";
      for (int dayOfWeekIndex = 0; dayOfWeekIndex < dayVoid2; ++dayOfWeekIndex) {
        cout << "\t" << " ";
      }
    }
    
    
    for (int index = 0; index < dayOfWeekCount - dayVoid2; ++index) {
      if (dayIndex2 == months.dayOfMonthCount[monthIndex + 6]) {
        for (int dayOfWeekIndex = 0; dayOfWeekIndex < dayOfWeekCount - dayOfWeekOfFirstDayOfMonth2;
         ++dayOfWeekIndex) {
          cout << "\t" << " ";
        }
        cout << "\t";
        break;
      } else {
        cout << "\t" << dayIndex2 + 1;
        ++dayIndex2;
        ++dayOfWeekOfFirstDayOfMonth2;
        
        if (dayOfWeekOfFirstDayOfMonth2 == dayOfWeekCount + 1) {
          dayOfWeekOfFirstDayOfMonth2 = 1;
        }
      }
    }
    
    cout << endl;
    dayVoid1 = 0;
    dayVoid2 = 0;
  }
  
  cout << "\n\n";
  
  --dayOfWeekOfFirstDayOfMonth;

  if (dayOfWeekOfFirstDayOfMonth == dayOfWeekCount) {
    dayOfWeekOfFirstDayOfMonth = 1;
  } else {
    ++dayOfWeekOfFirstDayOfMonth;
  }
}

int floorDiv(int divisor1, int divisor2) {  // функция целочисленного деления
  return floor(double(divisor1) / divisor2);
}

int floorMod(int divisor1, int divisor2) { // функция вычисления остатка от деления
  return divisor1 - divisor2 * floorDiv(divisor1, divisor2);
}

int main(){
  
  int year, dayOfWeekOfFirstDayOfMonth, dayOfMonth, monthNumber,
  yearOfCentury, centuryCount;
  
  bool yearLeap;
  
  cout << "Введите год: "; 
  cin  >> year;
  cout << endl;
  
  //cout << "\t\t\t     " << year << "\n";
  
  if (year % 4 == 0 || year % 400 == 0) {
    yearLeap = true;
    ++months.dayOfMonthCount[months.monthLeapIndex]; // прибавление доп. дня в високосном году.
  }
  
  dayOfMonth = 1;
  monthNumber = 10; // номер первого месяца в году для расчёта в формуле
  yearOfCentury = (year % 100);
  centuryCount = (year / 100);
  
  int a = floorDiv((14 - monthNumber), monthsCount); // переменная для формулы
  
  year -= a;
  monthNumber = monthNumber + monthsCount * a - 2;
  // две предыдущие строки — преобразования для формулы.
  
  dayOfWeekOfFirstDayOfMonth = floorMod((dayOfMonth + ( floorDiv((31 * monthNumber), monthsCount) ) // Определение дня недели первого дня в году.
  + year + floorDiv(year, 4) - floorDiv(year, 100) + floorDiv(year, 400)), dayOfWeekCount);
  
  if (dayOfWeekOfFirstDayOfMonth == 0) {
    dayOfWeekOfFirstDayOfMonth = dayOfWeekCount;
  }
  
  if (yearLeap) { // корректировки дня недели, в случае високосного года.
    if (dayOfWeekOfFirstDayOfMonth == 1) {
      dayOfWeekOfFirstDayOfMonth = dayOfWeekCount;
    } else {
      --dayOfWeekOfFirstDayOfMonth; 
    }
  }
  
  int dayOfWeekOfFirstDayOfMonth2;
  dayOfWeekOfFirstDayOfMonth2 = dayOfWeekOfFirstDayOfMonth;
  
  for (int monthIndex = 0; monthIndex < (monthsCount / 2); ++monthIndex) {
    Month(monthIndex, dayOfWeekOfFirstDayOfMonth, dayOfWeekOfFirstDayOfMonth2); // вывод календаря
  }
}
