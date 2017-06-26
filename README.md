# Taxi Pooling

This project was developed as part of the **CSE 323 Algorithms and Data Structures course**  ,Faculty Of Engineering Ain Shams University, Cairo, Egypt.

![Snapshot](http://i.imgur.com/08U5MZw.png "Snapshot 1")

## Usage
- git clone https://github.com/AhmedMostafaSoliman/Taxi-Pooling.git
- Open **Taxi-Pooling.pro** using _Qt_ 
- Run **qmake**
- Build
- Run 

## Background
- Breadth First Search​ is used to find the shortest path from each vacant taxi
to a customer, among them, the nearest one is assigned to the customer, then
The path itself is stored as a stack attribute in each taxi object to ease the
construction of the path/simulation process after finding the target in the
BFS, the steps are stored in the stack as characters (‘u’, ’l’, r’, ’d’).
(More details on how BFS is used to find shortest path can be found [here](http://stackoverflow.com/a/18778681/2762279))

## License

MIT License

Copyright (c) [2016] [Taxi-Pooling]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
