#include "raylib.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#define WIDTH 900
#define HEIGHT 400

using namespace std;

// global variabel countdown untuk swap
int countdown{3};
float run{};
float lastUpdate{0.03};

void draw(int *arr, int n, int widthVerticalBar, Color *arr_clr, Color *clr);

void bubbleSort(int *arr, int &sizeArr, int &widthVerticalBar, Color *arr_clr, Color *clr);

void insertionSort(int *arr, int &sizeArr, int &widthVerticalBar, Color *arr_clr, Color *clr, int &x);

void selectionSort(int *arr, int &sizeArr, int &widthVerticalBar, Color *arr_clr, Color *clr, int &t);

void merge(int *arr, int s, int e)
{
    int i = s;
    int mid = (s + e) / 2;
    int j = mid + 1;

    vector<int> temp;

    while (i <= mid and j <= e)
    {
        if (arr[i] < arr[j])
        {
            temp.push_back(arr[i]);
            i++;
        }
        else
        {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid)
    {
        temp.push_back(arr[i++]);
    }
    while (j <= e)
    {
        temp.push_back(arr[j++]);
    }

    int k = 0;
    for (int idx = s; idx <= e; idx++)
    {
        arr[idx] = temp[k++];
    }

    return;
}

void mergeSort(int *arr, int s, int e)
{
    if (s >= e)
        return;

    int mid = (s + e) / 2;

    mergeSort(arr, s, mid);
    mergeSort(arr, mid + 1, e);
    return merge(arr, s, e);
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Sorting visualization");
    SetTargetFPS(60);

    int sizeArr{40};
    int widthVerticalBar{WIDTH / sizeArr};
    // cout << widthVerticalBar << endl;
    int arr[sizeArr];
    Color arr_clr[sizeArr];
    Color clr[] = {YELLOW, DARKGREEN, DARKBLUE};
    string sortList[] = {"Bubble Sort", "Insertion Sort", "Selection Sort"};
    int sizeSort = sizeof(sortList) / sizeof(string);
    int select{};

    // variabel tracking
    // track current element di insertion sort
    int x = 1;
    // track current element di selection sort
    int t = 0;

    bool sort{};
    bool done{};

    // inisialisasi array saat pertama kali
    for (int i = 0; i < sizeArr; i++)
    {
        arr[i] = GetRandomValue(50, 200);
    }
    // inisialisasi array color saat pertama kali
    for (int i = 0; i < sizeArr; i++)
    {
        arr_clr[i] = clr[0];
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        draw(arr, sizeArr, widthVerticalBar, arr_clr, clr);

        if (IsKeyPressed(KEY_R) && !sort)
        {
            // tracking current element di insertion sort
            x = 0;
            done = false;
            // generate new random value array
            for (int i = 0; i < sizeArr; i++)
            {
                arr[i] = GetRandomValue(50, 200);
            }
        }

        if (IsKeyPressed(KEY_SPACE) && !sort)
        {
            sort = true;
        }

        if (!sort)
        {
            if (IsKeyPressed(KEY_ONE))
                select = 1;
            else if (IsKeyPressed(KEY_TWO))
                select = 2;
            else if (IsKeyPressed(KEY_THREE))
                select = 3;
        }

        if (sort)
        {
            run += GetFrameTime();
            if (run >= lastUpdate)
            {
                if (countdown != -1)
                    countdown--;
                run = 0.0;
            }
        }

        if (sort)
        {
            // TODO: merge sort sudah ditambah,
            // bikin cara untuk visualisasi merge sort

            // mergeSort(arr, 0, sizeArr - 1);
            if (select > 0)
            {
                if (select == 1)
                    bubbleSort(arr, sizeArr, widthVerticalBar, arr_clr, clr);
                else if (select == 2)
                    insertionSort(arr, sizeArr, widthVerticalBar, arr_clr, clr, x);
                else if (select == 3)
                    selectionSort(arr, sizeArr, widthVerticalBar, arr_clr, clr, t);
            }
        }

        if (countdown == -1)
        {
            sort = false;
            done = true;
        }

        // if (done)
        // {
        //     runDone += GetFrameTime();
        //     if (runDone >= lastDone)
        //     {
        //         if (count != -1)
        //             count--;
        //         runDone = 0.0;
        //     }
        // }

        // if (countdown < 0)
        // {
        //     sort = false;
        // }

        // Select sorting algorithm
        for (int i = 0; i < sizeSort; i++)
        {
            DrawText(sortList[i].c_str(), 120 + i * 250, 20, 20, WHITE);

            switch (select)
            {
            case 1:
                DrawText(sortList[0].c_str(), 120 + 0 * 250, 20, 20, ORANGE);
                break;
            case 2:
                DrawText(sortList[1].c_str(), 120 + 1 * 250, 20, 20, ORANGE);
                break;
            case 3:
                DrawText(sortList[2].c_str(), 120 + 2 * 250, 20, 20, ORANGE);
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void draw(int *arr, int n, int widthVerticalBar, Color *arr_clr, Color *clr)
{
    for (int i = 0; i < n; i++)
    {
        DrawRectangle(i * widthVerticalBar, HEIGHT - arr[i], widthVerticalBar, arr[i], arr_clr[i]);

        DrawRectangleLines(i * widthVerticalBar, HEIGHT - arr[i], widthVerticalBar, arr[i], BLACK);
    }
}

void bubbleSort(int *arr, int &sizeArr, int &widthVerticalBar, Color *arr_clr, Color *clr)
{
    for (int i = 1; i <= sizeArr - 1; i++)
    {
        _sleep(0.03);
        for (int j = 0; j <= sizeArr - i - 1; j++)
        {

            if (arr[j] > arr[j + 1] and countdown < 0)
            {
                arr_clr[j] = clr[1];
                arr_clr[j + 1] = clr[1];
                DrawRectangle(j * widthVerticalBar, HEIGHT - arr[j], widthVerticalBar, arr[j], arr_clr[j]);

                DrawRectangleLines(j * widthVerticalBar, HEIGHT - arr[j], widthVerticalBar, arr[j], BLACK);

                DrawRectangle(j * widthVerticalBar + widthVerticalBar, HEIGHT - arr[j + 1], widthVerticalBar, arr[j + 1], arr_clr[j + 1]);

                DrawRectangleLines(j * widthVerticalBar + widthVerticalBar, HEIGHT - arr[j + 1], widthVerticalBar, arr[j + 1], BLACK);
                arr_clr[j] = clr[0];
                arr_clr[j + 1] = clr[0];

                _sleep(0.03);
                swap(arr[j], arr[j + 1]);
                countdown = 3;
            }
        }
    }
}

void insertionSort(int *arr, int &sizeArr, int &widthVerticalBar, Color *arr_clr, Color *clr, int &x)
{
    for (int i = 1; i <= sizeArr - 1; i++)
    {

        _sleep(0.03);
        int currentEl = arr[i];
        int j = i - 1;

        DrawRectangle(x * widthVerticalBar, HEIGHT - arr[x + 1], widthVerticalBar, arr[x + 1], DARKBLUE);

        DrawRectangleLines(x * widthVerticalBar, HEIGHT - arr[x + 1], widthVerticalBar, arr[x + 1], BLACK);

        while (j >= 0 and arr[j] > currentEl && countdown < 0)
        {
            if (j > x)
            {
                x = j;
            }
            arr_clr[j] = clr[1];

            DrawRectangle(j * widthVerticalBar + widthVerticalBar, HEIGHT - arr[j + 1], widthVerticalBar, arr[j + 1], arr_clr[j]);

            DrawRectangleLines(j * widthVerticalBar, HEIGHT - arr[j + 1], widthVerticalBar, arr[j + 1], BLACK);

            arr[j + 1] = arr[j];

            DrawRectangle(j * widthVerticalBar, HEIGHT - arr[j], widthVerticalBar, arr[j], arr_clr[j]);

            DrawRectangleLines(j * widthVerticalBar, HEIGHT - arr[j], widthVerticalBar, arr[j], BLACK);

            _sleep(0.03);
            arr_clr[j] = clr[0];
            j = j - 1;
            countdown = 3;
        }

        _sleep(0.3);
        arr[j + 1] = currentEl;
        // _sleep(0.03);
        // arr_clr[i] = clr[0];
    }
}

void selectionSort(int *arr, int &sizeArr, int &widthVerticalBar, Color *arr_clr, Color *clr, int &t)
{
    for (int i = 0; i <= sizeArr - 2; i++)
    {
        _sleep(0.03);
        int min = i;

        DrawRectangle(t * widthVerticalBar, HEIGHT - arr[t], widthVerticalBar, arr[t], DARKBLUE);

        DrawRectangleLines(t * widthVerticalBar, HEIGHT - arr[t], widthVerticalBar, arr[t], BLACK);

        for (int j = i; j < sizeArr; j++)
        {
            if (arr[j] < arr[min] and countdown < 0)
            {
                t = min;

                arr_clr[j] = clr[1];
                DrawRectangle(j * widthVerticalBar, HEIGHT - arr[j], widthVerticalBar, arr[j], arr_clr[j]);

                DrawRectangleLines(j * widthVerticalBar, HEIGHT - arr[j], widthVerticalBar, arr[j], BLACK);
                arr_clr[j] = clr[0];

                min = j;
                countdown = 3;
            }
        }
        _sleep(0.03);
        swap(arr[min], arr[i]);
    }
}
