#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "AVL.h"
#include "BST.h"

using namespace std;

int main()
{
        AVL a1;
        Binary_Search_Tree object1;

    int N = 10;
    using chrono::nanoseconds;
    random_device rd;
    mt19937 gen(rd());

    //Set the random distribution
    uniform_int_distribution<int> dist(0, 100000);
    auto begin = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    //Write the header of CSV files
    ofstream dataFile("data.dat");
    dataFile << "Size,  Insert AVL,  Search AVL,  Insert BST,  Search BST ";
    dataFile<< "\n";

    // for random data
    nanoseconds total_insertAVL(0), average_insertAVL(0);
    nanoseconds total_searchAVL(0), average_searchAVL(0);
    nanoseconds total_insertBST(0), average_insertBST(0);
    nanoseconds total_searchBST(0), average_searchBST(0);
    // for ordered data
    nanoseconds total_insertAVL_order(0), average_insertAVL_order(0);
    nanoseconds total_searchAVL_order(0), average_searchAVL_order(0);
    nanoseconds total_insertBST_order(0), average_insertBST_order(0);
    nanoseconds total_searchBST_order(0), average_searchBST_order(0);
    // for low entropy data
    nanoseconds total_insertAVL3(0), average_insertAVL3(0);
    nanoseconds total_searchAVL3(0), average_searchAVL3(0);
    nanoseconds total_insertBST3(0), average_insertBST3(0);
    nanoseconds total_searchBST3(0), average_searchBST3(0);

    cout << "Size\t\t Insert AVL\t\t Search AVL\t Insert BST\t Search BST" << endl;
    cout << "------------------------------------------------------------------------------------------------------------\n";
    for (int j=N; j<7000; j+=100)
    {
        int* tempAVL_rand= new int [j];
        int* tempBST_rand= new int [j];

        for(int t = 0; t < 100; t++)
        {

            for(int i=0; i<j; i++)
            {
                tempAVL_rand[i] = tempBST_rand[i] = dist(gen);
            }

// --> RANDOM DATA <--

            begin = std::chrono::steady_clock::now();
            for(int x=0; x<j; x++)
            {
                a1.root = a1.Insert(a1.root, tempAVL_rand[x]);
            }
            end = chrono::steady_clock::now();
            nanoseconds time_insertAVL(end - begin);
            total_insertAVL += time_insertAVL;

            begin = std::chrono::steady_clock::now();

            // recursive search call
            a1.Search(200000);

            end = chrono::steady_clock::now();
            nanoseconds time_searchAVL(end - begin);
            total_searchAVL += time_searchAVL;

            begin = std::chrono::steady_clock::now();
            for(int x=0; x<j; x++)
            {
                if (x==0)
                    object1.setRoot(object1.Insert(object1.getRoot(), tempBST_rand[x]));
                else
                    object1.Insert(object1.getRoot(), tempBST_rand[x]);
            }
            end = chrono::steady_clock::now();
            nanoseconds time_insertBST(end - begin);
            total_insertBST += time_insertBST;

            begin = std::chrono::steady_clock::now();

            // recursive search call
            object1.Search(200000);

            end = chrono::steady_clock::now();
            nanoseconds time_searchBST(end - begin);
            total_searchBST += time_searchBST;
        }

        // time for random data
        average_insertBST= total_insertBST/100;
        average_searchBST= total_searchBST/100;
        average_insertAVL= total_insertAVL/100;
        average_searchAVL= total_searchAVL/100;

        cout << j << " \t\t " << average_insertAVL.count() << " \t\t " << average_searchAVL.count()<<  " \t\t "
             << average_insertBST.count() << " \t\t " << average_searchBST.count() << endl;

             //Write the data to CSV file
             dataFile << j << "," << average_insertAVL.count() << "," << average_searchAVL.count()<<  ","
             << average_insertBST.count() << "," << average_searchBST.count();
             dataFile<< "\n";

        delete [] tempAVL_rand;
        delete [] tempBST_rand;
    }
//    o.Display();
//    cout << endl;
//    cout << o.root->data << endl;
//    cout << o.root->height << endl;

    // --> ordered data <--

        AVL a2;
        Binary_Search_Tree object2;

        dataFile << "Ordered data";
        dataFile<< "\n";
        dataFile << "Size,  Insert AVL,  Search AVL,  Insert BST,  Search BST ";
        dataFile<< "\n";
        cout << "\nOrdered data\nSize\t Insert AVL\t Search AVL\t Insert BST\t Search BST" << endl;
    cout << "------------------------------------------------------------------------------------------------------------\n";
    for (int j=N; j<7000; j+=100)
    {
        int* tempAVL_order= new int [j];
        int* tempBST_order = new int [j];

        for(int t = 0; t < 100; t++)
        {

            for(int i=0; i<j; i++)
            {
                tempAVL_order[i] = tempBST_order[i] = i;
            }
// --> ORDERED DATA <--

            begin = std::chrono::steady_clock::now();
            for(int x=0; x<j; x++)
            {
                a2.root = a2.Insert(a2.root, tempAVL_order[x]);
            }
            end = chrono::steady_clock::now();
            nanoseconds time_insertAVL_order(end - begin);
            total_insertAVL_order += time_insertAVL_order;

            begin = std::chrono::steady_clock::now();

            // recursive search call
            a2.Search(200000);

            end = chrono::steady_clock::now();
            nanoseconds time_searchAVL_order(end - begin);
            total_searchAVL_order += time_searchAVL_order;

            begin = std::chrono::steady_clock::now();
            for(int x=0; x<j; x++)
            {
                if (x==0)
                    object2.setRoot(object2.Insert(object2.getRoot(), tempBST_order[x]));
                else
                    object2.Insert(object2.getRoot(), tempBST_order[x]);
            }
            end = chrono::steady_clock::now();
            nanoseconds time_insertBST_order(end - begin);
            total_insertBST_order+= time_insertBST_order;

            begin = std::chrono::steady_clock::now();

            // recursive search call
            object2.Search(200000);

            end = chrono::steady_clock::now();
            nanoseconds time_searchBST_order(end - begin);
            total_searchBST_order += time_searchBST_order;


        }

        // time for ordered data
        average_insertBST_order= total_insertBST_order/100;
        average_searchBST_order= total_searchBST_order/100;
        average_insertAVL_order= total_insertAVL_order/100;
        average_searchAVL_order= total_searchAVL_order/100;
        cout << j << "\t\t" << average_insertAVL_order.count() << "\t\t" << average_searchAVL_order.count()
             << "\t\t" << average_insertBST_order.count() << "\t\t" << average_searchBST_order.count()  << endl;
           //cout << "\n";  o.Display(); cout << "\n";

           dataFile << j << "," << average_insertAVL_order.count() << "," << average_searchAVL_order.count()<<  ","
                    << average_insertBST_order.count() << "," << average_searchBST_order.count();
           dataFile << "\n";


        delete [] tempAVL_order;
        delete [] tempBST_order;

    }

//    o.Display();    cout << endl;
//   cout << o.root->data << endl;
//    cout << o.root->height << endl;

// --> Low entropy data <-- \\

        AVL a3;
        Binary_Search_Tree object3;
    dataFile << "Low entropy data";
    dataFile<< "\n";
    dataFile << "Size,  Insert AVL,  Search AVL,  Insert BST,  Search BST ";
    dataFile<< "\n";
    cout << "\n LOW ENTROPY DATA \nSize\t Insert AVL\t Search AVL\t Insert BST\t Search BST" << endl;
    cout << "-----------------------------------------------------------------------------------------------\n";
    for (int j=N; j<7000; j+=100)
    {
        int* tempAVL_rand3= new int [j];
        int* tempBST_rand3= new int [j];

        for(int t = 0; t < 100; t++)
        {
            int r=1;
            for(int i=0; i<j; i++)
            {
                tempAVL_rand3[i] = tempBST_rand3[i] = r;
                r=4*i/5;
            }


            begin = std::chrono::steady_clock::now();
            for(int x=0; x<j; x++)
            {
                a3.root = a3.Insert(a3.root, tempAVL_rand3[x]);
            }
            end = chrono::steady_clock::now();
            nanoseconds time_insertAVL3(end - begin);
            total_insertAVL3 += time_insertAVL3;

            begin = std::chrono::steady_clock::now();

            // recursive search call
            a3.Search(1000000);

            end = chrono::steady_clock::now();
            nanoseconds time_searchAVL3(end - begin);
            total_searchAVL3 += time_searchAVL3;

            begin = std::chrono::steady_clock::now();
            for(int x=0; x<j; x++)
            {
                if (x==0)
                    object3.setRoot(object3.Insert(object3.getRoot(), tempBST_rand3[x]));
                else
                    object3.Insert(object3.getRoot(), tempBST_rand3[x]);
            }
            end = chrono::steady_clock::now();
            nanoseconds time_insertBST3(end - begin);
            total_insertBST3 += time_insertBST3;

            begin = std::chrono::steady_clock::now();

            // recursive search call
            object3.Search(1000000);

            end = chrono::steady_clock::now();
            nanoseconds time_searchBST3(end - begin);
            total_searchBST3 += time_searchBST3;
        }

        // time for random data
        average_insertBST3= total_insertBST3/100;
        average_searchBST3= total_searchBST3/100;
        average_insertAVL3= total_insertAVL3/100;
        average_searchAVL3= total_searchAVL3/100;

        cout << j << " \t\t " << average_insertAVL3.count() << " \t\t " << average_searchAVL3.count()<<  " \t\t "
             << average_insertBST3.count() << " \t\t " << average_searchBST3.count() << endl;

            dataFile << j << "," << average_insertAVL3.count() << "," << average_searchAVL3.count()<<  ","
                     << average_insertBST3.count() << "," << average_searchBST3.count();
            dataFile << "\n";

        delete [] tempAVL_rand3;
        delete [] tempBST_rand3;
    }
    dataFile.close();
//    o.Display();
//    cout << endl;
//    cout << o.root->data << endl;
//    cout << o.root->height << endl;


    return 0;
}
