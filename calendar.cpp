/********************************************************
 * Автор: Вяткин Владислав                              *
 * Группа: ПИ-221                                       *
 * Название: Календарь                                  *
 * Дата: 21.11.2022                                     *
 * Ссылка на OnlineGDB: https://onlinegdb.com/ob6z21aMz *
 ********************************************************/

#include <iostream>
#include <cmath>

using namespace std;

const int dayOfWeekCount = 7;
  
string dayOfWeek[dayOfWeekCount] = { "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ", "ВС" };

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
  
  cout << "\n";
}

void Month(int monthIndex, int& dayOfWeekOfFirstDayOfMonth) { // отрисовка месяца календаря
  cout << "\t";
  for (int index = 0; index < 50; ++index) {
    cout << "-";
  }
  cout << "\n";
  
  cout << "\t\t\t    " << months.monthsNames[monthIndex] << "\n\n";
  
  cout << "\t";
  Week();
  
  cout << "\t";
  for (int dayOfWeekIndex = 1; dayOfWeekIndex < dayOfWeekOfFirstDayOfMonth;
   ++dayOfWeekIndex) {
      cout << " " << "\t";
    }
  
  for (int dayIndex = 0; dayIndex < months.dayOfMonthCount[monthIndex]; ++dayIndex) {
    if (dayOfWeekOfFirstDayOfMonth == dayOfWeekCount + 1) {
      dayOfWeekOfFirstDayOfMonth = 1;
      cout << "\n\t";
    }
    
    cout << dayIndex + 1 << "\t";
    
    ++dayOfWeekOfFirstDayOfMonth;
  }
  
  cout << "\n\n";
  
  --dayOfWeekOfFirstDayOfMonth;

  if (dayOfWeekOfFirstDayOfMonth == dayOfWeekCount) {
    dayOfWeekOfFirstDayOfMonth = 1;
  } else {
    ++dayOfWeekOfFirstDayOfMonth;
  }
  
  cout << "\t";
  for (int index = 0; index < 50; ++index) {
    cout << "-";
  }
  cout << "\n";
}

int floorDiv(int divisor1, int divisor2) {  // функция целочисленного деления
  return floor(double(divisor1) / divisor2);
}

int floorMod(int divisor1, int divisor2) { // функция вычисления остатка от деления
  return divisor1 - divisor2 * floorDiv(divisor1, divisor2);
}

int main() {
  
  int year, dayOfWeekOfFirstDayOfMonth, dayOfMonth, monthNumber,
  yearOfCentury, centuryCount;
  
  bool yearLeap;
  
  cout << "Введите год: "; 
  cin  >> year;
  cout << endl;
  
  cout << "\t\t\t     " << year << "\n";
  
  if (year % 4 == 0 || year % 400 == 0) {
    yearLeap = true;
    ++months.dayOfMonthCount[months.monthLeapIndex]; // прибавление доп. дня в високосном году.
  }
  
  dayOfMonth = 1;
  monthNumber = 10; // номер первого месяца в году для расчёта в формуле
  yearOfCentury = (year % 100);
  centuryCount = (year / 100);
  
  int a = floorDiv((14 - monthNumber), 12); // переменная для формулы
  
  year -= a;
  monthNumber = monthNumber + 12 * a - 2;
  // две предыдущие строки — преобразования для формулы.
  
  dayOfWeekOfFirstDayOfMonth = floorMod((dayOfMonth + ( floorDiv((31 * monthNumber), 12) ) // Определение дня недели первого дня в году.
  + year + floorDiv(year, 4) - floorDiv(year, 100) + floorDiv(year, 400)), 7);
  
  if (dayOfWeekOfFirstDayOfMonth == 0) {
    dayOfWeekOfFirstDayOfMonth = 7;
  }
  
  if (yearLeap) {
    --dayOfWeekOfFirstDayOfMonth; // корректировки дня недели, в случае високосного года.
  }
  
  for (int monthIndex = 0; monthIndex < monthsCount; ++monthIndex) {
    Month(monthIndex, dayOfWeekOfFirstDayOfMonth); // вывод календаря
  }
}