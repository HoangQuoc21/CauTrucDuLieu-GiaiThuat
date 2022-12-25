#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#define maxn 1000
#define maxf 1000000000
using namespace std;

void gotoxy(int x,int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x-1,y-1};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

int u, v, B = 100;

void Check_Batery(char a[100][100], int n, int m);

void Inp(char a[100][100], int &n, int &m)
{
    ifstream in("robot.txt");
    in >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            in >> a[i][j];
            if(a[i][j] == '^' || a[i][j] == 'v' || a[i][j] == '<' || a[i][j] == '>')
            {
                u = i;
                v = j;
            }
        }
    in.close();
}

void Out(char a[100][100], int n, int m)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(j == 0) cout << "\t\t\t";
            if(a[i][j] == '^' || a[i][j] == 'v' || a[i][j] == '<' || a[i][j] == '>')
                SetColor(0, 4);
            else if(a[i][j] == '*') SetColor(0, 6);
            else if(a[i][j] == '#') SetColor(0, 3);
            else if(a[i][j] == '1') SetColor(0, 8);
            cout << a[i][j] << " ";
            SetColor(0, 15);
        }
        cout << "\n";
    }
}

void Up_n_step(char a[100][100], int n, int m, int l)
{
    int z;
    while(l != 0)
    {
        if(a[u][v] == '^')
        {
            int o = u;
            o--;
            if(a[o][v] == '1' || o < 0|| a[o][v] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[o][v] = a[u][v];
                l--;
                a[u][v] = '0';
                u--;
                B--;z=B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
        else if(a[u][v] == 'v')
        {
            int o = u;
            o++;
            if(a[o][v] == '1' || o >= n|| a[o][v] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[o][v] = a[u][v];
                l--;
                a[u][v] = '0';
                u++;
                B--;z=B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
        else if(a[u][v] == '>')
        {
            int o = v;
            o++;
            if(a[u][o] == '1' || o >= m|| a[u][o] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[u][o] = a[u][v];
                l--;
                a[u][v] = '0';
                v++;
                B--;z=B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
        else if(a[u][v] == '<')
        {
            int o = v;
            o--;
            if(a[u][o] == '1' || o < 0|| a[u][o] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[u][o] = a[u][v];
                l--;
                a[u][v] = '0';
                v--;
                B--;z=B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
    }
}

void Down_n_step(char a[100][100], int n, int m, int l)
{
    int z;
    while(l != 0)
    {
        if(a[u][v] == '^')
        {
            int o = u;
            o++;
            if(a[o][v] == '1' || o >= n || a[o][v] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[o][v] = a[u][v];
                l--;
                a[u][v] = '0';
                u++;
                B--;z = B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
        else if(a[u][v] == 'v')
        {
            int o = u;
            o--;
            if(a[o][v] == '1' || o < 0 || a[o][v] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[o][v] = a[u][v];
                l--;
                a[u][v] = '0';
                u--;
                B--;z = B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
        else if(a[u][v] == '>')
        {
            int o = v;
            o--;
            if(a[u][o] == '1' || o < 0|| a[u][o] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[u][o] = a[u][v];
                l--;
                a[u][v] = '0';
                v--;
                B--;z = B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
        else if(a[u][v] == '<')
        {
            int o = v;
            o++;
            if(a[u][o] == '1' || o >= m|| a[u][o] == '#')
            {
                cout << "\nGap chuong ngai vat. Ket thuc";
                Sleep(2000);
                return;
            }
            else
            {
                a[u][o] = a[u][v];
                l--;
                a[u][v] = '0';
                v++;
                B--;z = B;
                system("cls");
                Out(a, n, m);
                Sleep(1000);
                Check_Batery(a, n, m);
                if(z <= 0) return;
            }
        }
    }
}

struct Oxy
{
    int x, y;
};
int dinh, canh, d, pinx, piny,zB=0;
int Ca = 0, Di[1000][1000], c[100][100];
int f[maxn],trace[maxn],checkt2[maxn];
Oxy o[10000], b[1000];

void dijkstra(int s, int e)
{
    for(int i=1;i<=dinh;i++)
    {
        f[i]=maxf;
        checkt2[i]=true;
        trace[i]=0;
    }
    f[s]=0;
    trace[s]=0;
    int v=s,fmin;
    while(v!=e)
    {
        //tim v
        fmin=maxf;
        for(int i=1;i<=dinh;i++)
        if(checkt2[i] && fmin>f[i])
        {
            fmin=f[i];
            v=i;
        }
        if(fmin==maxf) break;
        //xoa v khoi T2
        checkt2[v]=false;
        //toi uu cac dinh trong T2
        for(int i=1;i<=dinh;i++)
        if(Di[v][i]>0 && f[i]>f[v]+Di[v][i])
        {
            f[i]=f[v]+Di[v][i];
            trace[i]=v;
        }
  }
}

void output(int e, Oxy o[], char a[100][100], int n, int m)
{
    int p, q, z = 0;
    int path[maxn];
    if(f[e]==maxf) cout<<"NO PATH";
    else
    {
        path[maxn];
        int d=0;
        d++;
        path[d]=e;
        while(trace[e]!=0)
        {
            e=trace[e];
            d++;
            path[d]=e;
        }
        for(int i=d;i>1;i--)
        {
            p = o[path[i]].x; u = p;
            q = o[path[i]].y; v = q;
            if(o[path[i]].y < o[path[i-1]].y) a[p][q] = '>';
            else if(o[path[i]].y > o[path[i-1]].y) a[p][q] = '<';
            else if(o[path[i]].x < o[path[i-1]].x) a[p][q] = 'v';
            else if(o[path[i]].x > o[path[i-1]].x) a[p][q] = '^';
            Out(a, n, m);
            Sleep(200);
            B--;
            int z = B;
            if(z > 0)a[p][q] = '0';
            Check_Batery(a, n, m);
            if(z <= 0) goto jump;
            system("cls");
        }
    }
    p = o[path[1]].x;u = p;
    q = o[path[1]].y;v = q;
    if(o[path[1]].y < o[path[2]].y) a[p][q] = '<';
    else if(o[path[1]].y > o[path[2]].y) a[p][q] = '>';
    else if(o[path[1]].x < o[path[2]].x) a[p][q] = '^';
    else if(o[path[1]].x > o[path[2]].x) a[p][q] = 'v';
    return;
    jump: system("cls"); return;
}

void Set_up(char a[100][100], int n, int m)
{
    d = -1;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            if(a[i][j] == '*')
            {
                d++;
                b[d].x = i;
                b[d].y = j;
            }
            if(a[i][j-1] == '#' && a[i+1][j] == '#')
            {
                pinx = i;
                piny = j;
            }
        }
    for(int i=1;i<=dinh;i++)
        for(int j=1;j<=dinh;j++) Di[i][j]=-1;
    int k = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            if(a[i][j] != '1' && a[i][j] != '#')
            {
                k++;
                c[i][j] = k;
                o[k].x = i;
                o[k].y = j;
            }else c[i][j] = 0;
        }

    for(int i = -1; i <= m; i++)
    {
        c[-1][i] = 0;
        c[n][i] = 0;
    }
    for(int i = -1; i <= n; i++)
    {
        c[i][-1] = 0;
        c[i][m] = 0;
    }
    for(int i = -1; i <= n; i++)
        for(int j = -1; j <= m; j++)
        {
            if(c[i][j] != 0)
            {
                if(c[i][j + 1] != 0)
                {
                    Ca++;
                    Di[c[i][j]][c[i][j+1]] = 1;
                    Di[c[i][j+1]][c[i][j]] = 1;
                }
                if(c[i+1][j] != 0)
                {
                    Ca++;
                    Di[c[i][j]][c[i+1][j]] = 1;
                    Di[c[i+1][j]][c[i][j]] = 1;
                }
            }
        }

    dinh = n*m;
}

void Auto_Move(char a[100][100], int n, int m)
{
    if(abs(u - b[d].x) < abs(u - b[0].x))
    {
        for(int k = d; k >= 0; k--)
        {
            if(a[b[k].x][b[k].y] != '*') continue;
            dijkstra(c[u][v], c[b[k].x][b[k].y]);
            output(c[b[k].x][b[k].y], o, a, n, m);
            if(a[b[k].x][b[k].y] == '*') goto jump;
        }
        return;
    }
    else
    {
        for(int k = 0; k <= d; k++)
        {
            if(a[b[k].x][b[k].y] != '*') continue;
            dijkstra(c[u][v], c[b[k].x][b[k].y]);
            output(c[b[k].x][b[k].y], o, a, n, m);
            if(a[b[k].x][b[k].y] == '*') goto jump;
        }
        return;
    }
    jump:Auto_Move(a, n, m);
}

void Recharge(char a[100][100], int n, int m)
{
    if(B - 2000 == 100)
    {
        B = B - 2000;
        cout << "\n                                                DA SAC DAY\n";
        cout << "0% =================================================================================================== 100%\n\n";
        system("pause");
        return;
    }
    dijkstra(c[u][v], c[pinx][piny]);
    output(c[pinx][piny], o, a, n, m);
    Out(a, n, m);B++;
    if(B>100 && B <= 1000) B= B - 1000;
    if(B>1000) B = B - 2000;
    if(B <= 0) B = 0;
    cout << "\n\n\t\t\t\t\t\t  PIN DANG SAC";
    cout << "\n0% ";
    int xi = n + 4, yi = 4;
    for(int i = 1; i <= B; i++)
    {
        yi++;
        cout << "=";
    }
    while(B != 100)
    {
        B++;
        gotoxy(yi, xi);
        cout << "=";
        yi++;
        gotoxy(105, n+4);
        cout << B << "%";
        Sleep(50);
    }
    cout << "\n\t\t\t\t\t\t   DA SAC DAY\n\n";
    system("pause");
}
void MENU(char a[100][100], int n, int m)
{
    while(true)
    {
        system("cls");
        cout << "\n\n\t\t ================= MENU FUNCTION OF ROBOT =================";
        cout << "\n\t\t Ten thuong hieu: GROUP5VIPRO";
        cout << "\n\t\t Ma so san pham: 4063115972";
        cout << "\n\t\t Robot con " << B << "%";
        cout << "\n\t\t 1. Huong di chuyen";
        cout << "\n\t\t 2. Tien len n buoc";
        cout << "\n\t\t 3. Lui lai n buoc";
        cout << "\n\t\t 4. Xoay trai 90 do";
        cout << "\n\t\t 5. Xoay phai 90 do";
        cout << "\n\t\t 6. Xoay 180 do";
        cout << "\n\t\t 7. Tu dong hut bui";
        cout << "\n\t\t 8. Sac pin";
        cout << "\n\t\t 0. Ket thuc";
        cout << "\n\t\t ========================== END ===========================";
        Set_up (a, n, m);
        cout << "\n\t\t\t\t  VI TRI HIEN TAI CUA ROBOT\n";
        Out(a, n, m);

        int choice;
        cout << "\nNhap lua chon: ";
        cin >> choice;
        while(choice < 0 || choice > 8)
        {
            cout << "\nLua chon khong hop le. Vui long nhap lai: ";
            cin >> choice;
        }
        if(choice == 1)
        {
            B--;
            Check_Batery(a, n, m);
            char x;
            cout << "\nBan muon di chuyen theo huong ^(Bac), v(Nam), >(Dong) hay <(Tay): ";
            cin >> x;
            while(x != '^' && x != 'v' && x != '>' && x != '<')
            {
                cout << "\nLua chon khong hop le. Vui long nhap lai: ";
                cin >> x;
            }
            a[u][v] = x;
            cout << "\n\t\t\t   VI TRI ROBOT SAU KHI HUONG THAY DOI\n";
            Out(a, n, m);
            system("pause");
            continue;
        }
        else if(choice == 2)
        {
            int l;
            cout << "\nNhap gia tri n: ";
            cin >> l;
            Up_n_step(a, n, m, l);
        }
        else if(choice == 3)
        {
            int l;
            cout << "\nNhap gia tri n: ";
            cin >> l;
            Down_n_step(a, n, m, l);
        }
        else if(choice == 4)
        {
            if(a[u][v] == '^') a[u][v] = '<';
            else if(a[u][v] == 'v') a[u][v] = '>';
            else if(a[u][v] == '<') a[u][v] = 'v';
            else if(a[u][v] == '>') a[u][v] = '^';
            cout << "\n\t\t\t       VI TRI ROBOT SAU KHI XOAY TRAI 90 DO\n";
            Out(a, n, m);
            B--;
            Check_Batery(a, n, m);
            system("pause");
            continue;
        }
        else if(choice == 5)
        {
            if(a[u][v] == '^') a[u][v] = '>';
            else if(a[u][v] == 'v') a[u][v] = '<';
            else if(a[u][v] == '<') a[u][v] = '^';
            else if(a[u][v] == '>') a[u][v] = 'v';
            cout << "\n\t\t\t       VI TRI ROBOT SAU KHI XOAY PHAI 90 DO\n";
            Out(a, n, m);
            B--;
            Check_Batery(a, n, m);
            system("pause");
            continue;
        }
        else if(choice == 6)
        {
            if(a[u][v] == '^') a[u][v] = 'v';
            else if(a[u][v] == 'v') a[u][v] = '^';
            else if(a[u][v] == '<') a[u][v] = '>';
            else if(a[u][v] == '>') a[u][v] = '<';
            cout << "\n\t\t\t       VI TRI ROBOT SAU KHI XOAY 180 DO\n";
            Out(a, n, m);
            B--;
            Check_Batery(a, n, m);
            system("pause");
            continue;
        }
        else if(choice == 7)
        {
            Auto_Move(a, n, m);
        }
        else if(choice == 8)
        {
            B = B + 2000;
            Recharge(a, n, m);
        }
        else break;

    }
}

int main()
{
    char a[100][100];
    int n, m;
    Inp(a, n, m);
    MENU(a, n, m);
}

void Check_Batery(char a[100][100], int n, int m)
{
    if(B == 15 || B == 10 || B == 5)
    {
        cout << "\nSap het pin. Con lai " << B << "%\n";
        system("pause");
    }
    else if(B <= 0)
    {
        int choice;
        cout << "\nROBOT DA HET PIN";
        cout << "\n1. Thay pin moi";
        cout << "\n2. Tu dong sac";
        cout << "\nVUI LONG LUA CHON: ";
        cin >> choice;
        while(choice != 1 && choice != 2)
        {
            cout << "\nLua chon khong hop le. Vui long nhap lai: ";
            cin >> choice;
        }
        if(choice == 1)
        {
            cout << "\n                                                DA SAC DAY\n";
            cout << "0% =================================================================================================== 100%\n\n";
            system("pause");
            B = 100;
        }
        else if(choice == 2) {B=1000; Recharge(a, n, m);}
    }
}
