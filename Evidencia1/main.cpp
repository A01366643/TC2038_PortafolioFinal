/*
Integrantes:
- Fernando López Gómez (A01639715)
- Fausto Alejandro Palma Cervantes (A01639224)
- Luisa Fernanda Castaños Arias (A01366643)
Compilar:
  g++ main.cpp -o main
Ejecutar:
  ./main
(https://onlinerandomtools.com/generate-random-string)
- Las posiciones dentro de cada parte inician en 1.
- Todas las funciones dentro del programa reciben un string con los contenidos del archivo correspondiente. Por ende, las funciones no serían muy eficientes para archivos muy grandes. En caso de utilizar archivos grandes se necesitaría recurrir a una estrategia de lectura diferente (ej. implementar una estructura dinámica y un buffer que trabajaran de manera simultánea.)
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Complejidad computacional: O(n)
std::string readFile(std::string fileName){
  std::string line, myString;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while(std::getline(file,line)) {
      myString += line;
    }
    file.close();
    return myString;
  }
}

// Complejidad computacional O(n)
std::vector<int> createTable(std::string &mcode){
  std::vector<int> table;
  int i = 0;
  table.push_back(0);
  for(int j = 1; j < mcode.length(); j++) {
    if(mcode[i] == mcode[j]) {
      table.push_back(i);
      i++;
    } else {
      table.push_back(0);
    }
  }
  return table;
}

// Complejidad computacional O(n)
int kmpAlgorithm(std::string &mcode, std::string &transmission) {
  std::vector<int> table = createTable(mcode);
  int i = 0, j = 0;
  while(j < mcode.length() && i < transmission.length()){
    // std::cout << "I: " << i << " J: " << j << " | " << mcode[j] << " == " << transmission[i] << std::endl;
    if(mcode[j] == transmission[i]){
      j++;
      i++;
    } else {
      if(j == 0) {
        i++;
      }
      j = table[j];
    }
  }
  if(j == mcode.length()) {
    return i - (mcode.length() - 1);
  } else {
    return -1;
  }
}

// Complejidad computacional O(n)
void partOne(std::string &mcode, std::string &transmission) {
  int result = kmpAlgorithm(mcode, transmission);
  if(result < 0) {
    std::cout << std::boolalpha << "  " << false << std::endl;
  } else {
    std::cout << std::boolalpha << "  " << true << " " << result << std::endl;
  }
}

// Complejidad computacional O(n)
void partTwo(std::string &transmission){
  int N = transmission.length();
  if (N == 0){
    return;
  }
  N = 2 * N + 1;
  int Length[N];
  Length[0] = 0;
  Length[1] = 1;
  int Center = 1;
  int Right = 2;
  int iMirror;
  int expand = -1;
  int diff = -1;
  int maxLength = 0;
  int maxCenterPosition = 0;
  int start = -1;
  int end = -1;
  for (int i = 2; i < N; i++) {
    iMirror = 2 * Center - i;
    expand = 0;
    diff = Right - i;
    if (diff >= 0) {
      if (Length[iMirror] < diff)
        Length[i] = Length[iMirror];
      else if (Length[iMirror] == diff && Right == N - 1)
        Length[i] = Length[iMirror];
      else if (Length[iMirror] == diff && Right < N - 1) {
        Length[i] = Length[iMirror];
        expand = 1;
      }
      else if (Length[iMirror] > diff) {
        Length[i] = diff;
        expand = 1;
      }
    } else {
      Length[i] = 0;
      expand = 1;
    }
    if (expand == 1) {
      while (((i + Length[i]) < N && (i - Length[i]) > 0)
      && (((i + Length[i] + 1) % 2 == 0)
      || (transmission[(i + Length[i] + 1) / 2]
      == transmission[(i - Length[i] - 1) / 2]))) {
        Length[i]++;
      }
    }
    if (Length[i] > maxLength) {
      maxLength = Length[i];
      maxCenterPosition = i;
    }
    if (i + Length[i] > Right) {
      Center = i;
      Right = i + Length[i];
    }
  }
  start = ((maxCenterPosition - maxLength) / 2) + 1;
  end = (start + maxLength - 1);
  std::cout << "  " << start << " " << end << std::endl;
}

// Complejidad computacional: O(n^2 * m)
int LCS(std::string str1, std::string str2, int N, int M, int &s, int &f) {
  //Longest common substring
  int LCSuff[N + 1][M + 1];
  int startIndex = 0, finishIndex = 0;
  bool firstMatch = true, newMax = false;
  int mx = 0;
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= M; j++) {
      if (i == 0 || j == 0) {
        LCSuff[i][j] = 0;
      }
      else if (str1[i - 1] == str2[j - 1]) {
        if (firstMatch){
          finishIndex = i; 
          firstMatch = false;
        }
        LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
        mx = std::max(mx, LCSuff[i][j]);
        if(LCSuff[i][j] == mx){
            newMax = true;
        }
      } 
      else{
        if(newMax){
            f = finishIndex;
        }
        firstMatch = true;
        newMax = false;
        LCSuff[i][j] = 0;
      }
            
    }
  }
  s = f - mx + 1;
  // std::cout << "startIndex: " << s << "Char: " << str1[s - 1]<< std::endl;
  // std::cout << "finishIndex: " << f << "Char: " << str1[f - 1]<< std::endl;
  return mx;
}
      
int main() {
  std::string transmission1, transmission2, mcode1, mcode2, mcode3;
  try{
    // Read files
    transmission1 = readFile("transmission1.txt");
    transmission2 = readFile("transmission2.txt");
    mcode1 = readFile("mcode1.txt");
    mcode2 = readFile("mcode2.txt");
    mcode3 = readFile("mcode3.txt");
    
  }
  catch (std::invalid_argument e) {std::cout << "ERROR: " << e.what() << std::endl;}
  
  if(transmission1 == "" || transmission2 == "" || mcode1 == "" || mcode2 == "" || mcode3 == ""){
    std::cout << "ERROR: Some files are empty" << std::endl; exit(0);
  }

  // Part 1 (https://www.youtube.com/watch?v=BXCEFAzhxGY)  
  std::cout << "parte 1" << std::endl;
  partOne(mcode1, transmission1);
  partOne(mcode2, transmission1);
  partOne(mcode3, transmission1);
  partOne(mcode1, transmission2);
  partOne(mcode2, transmission2);
  partOne(mcode3, transmission2);

  // Part 2 (https://medium.com/hackernoon/manachers-algorithm-explained-longest-palindromic-substring-22cb27a5e96f)
  std::cout << "parte 2" << std::endl;
  partTwo(transmission1);
  partTwo(transmission2);

  // Part 3
  std::cout << "parte 3" << std::endl;
  int start = 1, finish = 1;
  // Find longest common substring
  int length = LCS(transmission1, transmission2, transmission1.length(),  transmission2.length(), start, finish);
  // std::cout << "The longest common substring is of length: " << length << std::endl;
  std::cout << "  " << start << " " << finish << std::endl;

  return 0;
}