// ConsoleCArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CArray.h"
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>  


using namespace std;

int main()
{
  CArray<int> iArr;

  // 1.1.  добавление  в  цикле  20  случайных  чисел в диапазоне  от  0 до  100.
  time_t seconds;
  seconds = time(NULL);
  srand(seconds);

  for (int i = 0; i < 20; i++)
  {
    iArr.push_back(rand() % 101);
  }
  
  cout << endl << "1.1. 20 random numbers:" << endl;
  iArr.print();
  
  // 1.2. упорядочивание получившегося набора чисел по возрастанию.
  for (int i = 0; i < iArr.size(); i++)
  {
    for (int j = i+1; j < iArr.size(); j++)
    {
      if (iArr[i] > iArr[j])
      {
        int tmp = iArr[j];
        iArr[j] = iArr[i];
        iArr[i] = tmp;
      }
    }
  }

  cout << endl << "1.2. Sorting:" << endl;
  iArr.print();

  // 1.3. удаление каждого 2 элемента.
  int i = iArr.size() - 1;
  if (iArr.size() % 2)
  {
    i = iArr.size() - 2;
  }
  while (i > 0)
  {
    iArr.erase(i);
    i -= 2;
  }
  
  cout << endl << "1.3. deleted every second item:" << endl;
  iArr.print();

  // 1.4. вставка 10 случайных чисел в диапазоне от 0 до 100 на случайные позиции.
  for (int i = 0; i < 10; i++)
  {
    iArr.insert(rand() % iArr.size(), rand() % 101);
  }
  cout << endl << "1.4. inserting 10 random numbers:" << endl;
  iArr.print();

  // 1.5. очистка контейнера
  iArr.clear();
  cout << endl << "1.5. container cleaning:" << endl;
  iArr.print();
  
  // 2.1. добавление в цикле 15 случайно выбранных слов, состоящих из латинских букв в нижнем регистре.
  cout << endl << "2.1. 15 random words:" << endl;
  CArray<string> sArr;

  std::ifstream infile("words.txt");
  
  if (infile.is_open())
  {
    std::string line;
    CArray<string> lines;

    while (getline(infile, line)) {
      lines.push_back(line);
    }
    infile.close();

    for (int i = 0; i < 15; i++)
    {
      unsigned int index = rand() % lines.size();
      sArr.push_back(lines[index]);
    }

    sArr.print();
  }
  else
  {
    cout << "'words.txt' not found.." << endl;
  }
  
  // 2.2. упорядочивание получившегося набора слов по возрастанию.
  cout << endl << "2.2. sorting words:" << endl;
  for (int i = 0; i < sArr.size(); i++)
  {
    for (int j = i + 1; j < sArr.size(); j++)
    {
      if (sArr[i] > sArr[j])
      {
        std::string tmp = sArr[j];
        sArr[j] = sArr[i];
        sArr[i] = tmp;
      }
    }
  }
  sArr.print();

  // 2.3. удаление каждого слова, включающего в себя любую из буквa, b, c, d, e.
  cout << endl << "2.3. deleting words contains of any of these letters: b, c, d, e:" << endl;
  for (int i = sArr.size()-1; i >= 0; i--)
  {
    if ((sArr[i].find('b') != std::string::npos) ||
        (sArr[i].find('c') != std::string::npos) ||
        (sArr[i].find('d') != std::string::npos) ||
        (sArr[i].find('e') != std::string::npos))
    {
      sArr.erase(i);
    }
  }
  sArr.print();
  
  // 2.4. вставка 3 новых случайно выбранных слов на случайные позиции
  cout << endl << "2.4. inserted 3 new random words:" << endl;
  std::ifstream infile2("words.txt");

  if (infile2.is_open())
  {
    std::string line;
    CArray<string> lines;

    while (getline(infile2, line)) {
      lines.push_back(line);
    }
    infile2.close();

    int searchWords = 3;
    int tryLimit = 1000;
    while (searchWords)
    {
      unsigned int index = rand() % lines.size();
      std::string newWord = lines[index];
      bool isNewWord = true;
      for (int i = 0; i < sArr.size(); i++)
      {
        if (newWord == sArr[i])
        {
          isNewWord = false;
          break;
        }
      }
      
      if (isNewWord)
      {
        unsigned int index = rand() % sArr.size();
        sArr.insert(index, newWord);
        --searchWords;
      }
      else
      {
        --tryLimit;
      }

      if (!tryLimit)
        break;
    }

    if (!tryLimit)
      cout << "New words not found.." << endl;

    sArr.print();
  }
  else
  {
    cout << "'words.txt' not found.." << endl;
  }

  cout << endl;
  system("PAUSE");
  return 0;
}

