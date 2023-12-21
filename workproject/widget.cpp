#include "widget.h"
#include "ui_widget.h"
#include<QVector>
#include<QMessageBox>
#include<QMap>
#include<QString>
#include<QPainter>
#include<arrres.h>
#include<QDebug>


int RandomNumber;
int select=0;
int f=false;

int grid[9][9];
bool isaccess[9][9];
int ans[9][9];
int sel1[9][9];
QVector<QVector<int>> start(9, QVector<int>(9, 0));


void dfs(int grid[][9],int i,int j);
void getGrid();
bool check(int grid[][9]);



int arr[100][9][9]={

};

//初始化地图
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPalette pal =this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/C:/Users/27212/Desktop/aaa.jpeg")));
    setPalette(pal);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    for(int i=0;i<9;i++)
    {
        ui->tableWidget->setColumnWidth(i,65);
        ui->tableWidget->setRowHeight(i,65);
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem("x"));
        }
    }
    for (int i = 0; i<9; i++)
    {
        for (int j = 0; j<9; j++)
        {
            ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            ui->tableWidget->item(i, j)->setForeground(Qt::red);
        }
    }

}


//析构地图
Widget::~Widget()
{
    delete ui;
}


// 检查数字num是否可以放置在start[row][col]位置
bool isSafe(QVector<QVector<int>>& start, int row, int col, int num) {
    // 检查同一行和同一列
    for (int i = 0; i < 9; ++i) {
        if (start[row][i] == num || start[i][col] == num) {
            return false;
        }
    }

    // 检查所在的小九宫格
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (start[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// 递归生成数独题目
bool generateSudoku(QVector<QVector<int>>& start) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (start[row][col] == 0) {
                // 随机生成数字序列
                QVector<int> nums;
                for (int num = 1; num <= 9; ++num) {
                    nums.push_back(num);
                }
                std::random_shuffle(nums.begin(), nums.end());

                for (int num : nums) {
                    if (isSafe(start, row, col, num)) {
                        start[row][col] = num;
                        if (generateSudoku(start)) {
                            return true;
                        }
                        start[row][col] = 0;  // 回溯
                    }
                }
                return false;  // 无解
            }
        }
    }
    return true;  // 数独已填满
}

//随机函数
void digHoles(QVector<QVector<int>>& start, int numHoles) {
    for (int i = 0; i < numHoles; ++i) {
        int row = rand() % 9;
        int col = rand() % 9;
        start[row][col] = 0;
    }
}

//清空表格内容，回到初始状态
void Widget::on_pushButton_2_clicked()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            grid[i][j]=0;
            isaccess[i][j]=0;
            ans[i][j]=0;
            sel1[i][j]=0;
            start[i][j]=0;
            arr[0][i][j]=0;
            select=0;
            f=false;
        }
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem("x"));
            ui->tableWidget->item(i, j)->setForeground(Qt::red);
            ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    QMessageBox msgBox;
     msgBox.setText("内容已清空");
     msgBox.setStandardButtons(QMessageBox::Ok);
     int ret = msgBox.exec();
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

//检查答案是否符合要求
bool check(int grid[][9])
{
    QMap<int,int> mp;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    qDebug()<<"1";
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=3;i<6;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    qDebug()<<"2";
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=6;i<9;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=0;i<3;i++)
    {
        for(int j=3;j<6;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=3;i<6;i++)
    {
        for(int j=3;j<6;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=6;i<9;i++)
    {
        for(int j=3;j<6;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=0;i<3;i++)
    {
        for(int j=6;j<9;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=3;i<6;i++)
    {
        for(int j=6;j<9;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=6;i<9;i++)
    {
        for(int j=6;j<9;j++)
        {
            if(grid[i][j])
                {
                if(mp[grid[i][j]]==0)
                mp[grid[i][j]]++;
                else
                {
                    return false;
                }
            }
        }
    }
    mp.clear();
    for(int i=0;i<9;i++)
    {
        QMap<int,int> mp1;
        for(int j=0;j<9;j++)
        {
            if(mp1[grid[i][j]])
            {
                qDebug()<<"3";
                return false;
            }
            mp1[grid[i][j]]++;
        }
    }
    for(int i=0;i<9;i++)
    {
        QMap<int,int>mp1;
        for(int j=0;j<9;j++)
        {
            if(mp1[grid[j][i]])
            {
                qDebug()<<"4";
                return false;
            }
            mp1[grid[j][i]]++;
        }
    }
    return true;
}

//检查答案是否符合要求
bool _isTrue(int arr[][9],int x, int y, int l, int u,int z)
{
    int t = 0;
    for (int i = l; i < l+3; i++)
    {
        for (int j = u; j < u + 3; j++)
        {
            if (arr[i][j] == z)
            {
                t++;
            }
        }
    }
    if (t >= 1)
    {
        return false;
    }
    return true;
}

//检查现场答案是否符合要求
bool isTrue(int arr[][9],int x, int y,int z)
{
    if (x >= 0 && x < 3)
    {
        if (y >= 0 && y < 3)
        {
            if (_isTrue(arr,x, y, 0,0,z)==false)
            {
                return false;
            }
        }
        else if (y >= 3 && y < 6)
        {
            if (_isTrue(arr,x, y, 0, 3,z) == false)
            {
                return false;
            }
        }
        else if (y >= 6 && y < 9)
        {
            if (_isTrue(arr,x, y, 0, 6,z) == false)
            {
                return false;
            }
        }
    }
    else if (x >= 3 && x < 6)
    {
        if (y >= 0 && y < 3)
        {
            if (_isTrue(arr,x, y, 3, 0,z) == false)
            {
                return false;
            }
        }
        else if (y >= 3 && y < 6)
        {
            if (_isTrue(arr,x, y, 3, 3,z) == false)
            {
                return false;
            }
        }
        else if (y>=6&&y<9)
        {
            if (_isTrue(arr,x, y, 3, 6,z) == false)
            {
                return false;
            }
        }
    }
    else if(x >= 6 && x < 9)
    {
        if (y >= 0 && y < 3)
        {
            if (_isTrue(arr,x, y, 6, 0,z) == false)
            {
                return false;
            }
        }
        else if (y >= 3 && y < 6)
        {
            if (_isTrue(arr,x, y, 6, 3,z) == false)
            {
                return false;
            }
        }
        else if (y>=6&&y<9)
        {
            if (_isTrue(arr,x, y, 6, 6,z) == false)
            {
                return false;
            }
        }
    }
    for (int i = 0; i < y; i++)
    {
        if (arr[x][i] ==z)
        {
            return false;
        }
    }
    for (int j = 8; j>y; j--)
    {
        if (arr[x][j] == z)
        {
            return false;
        }
    }
    for (int i = 0; i < x; i++)
    {
        if (arr[i][y] == z)
        {
            return false;
        }
    }
    for (int j = 8; j>x; j--)
    {
        if (arr[j][y] == z)
        {
            return false;
        }
    }
    return true;
}

//提交答案并判断是否符合要求
void Widget::on_pushButton_3_clicked()
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            QString str=ui->tableWidget->item(i,j)->text();
            int num=str.toInt();
            grid[i][j]=num;
        }
    }
    bool c=false;
    for(int i=0;i<9;i++)
    {
        int cnt=0;
        for(int j=0;j<9;j++)
        {
            if(grid[i][j]==0||grid[i][j]>9)
            {
                c=true;
                cnt=1;
                QMessageBox msgBox;
                 msgBox.setText("输入不合法");
                 msgBox.setStandardButtons(QMessageBox::Ok);
                 msgBox.exec();
                 break;
            }
        }
        if(cnt)
        {
            break;
        }
    }
    if(c==false)
    {
        if(check(grid)==false)
        {
            QMessageBox msgBox;
             msgBox.setText("答案错误");
             msgBox.setStandardButtons(QMessageBox::Ok);
             msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
             msgBox.setText("答案正确");
             msgBox.setStandardButtons(QMessageBox::Ok);
             msgBox.exec();
        }
    }
}

//初始化棋盘
void Widget::on_pushButton_clicked()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            start[i][j]=0;
            arr[0][i][j]=0;
        }
    }
    srand((unsigned)time(NULL));
    if (generateSudoku(start)) {
            int numHoles = 60;
            digHoles(start, numHoles);
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (start[i][j] == 0) {
                        start[i][j]='x';
                    }
                }
            }
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    arr[0][i][j]=start[i][j];
                }
            }

        }
    RandomNumber = 0 ;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            int t=arr[RandomNumber][i][j];
            if(t<10)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(arr[RandomNumber][i][j])));
                ui->tableWidget->item(i, j)->setForeground(Qt::red);
                QTableWidgetItem* pItem = ui->tableWidget->item(i, j);
                 pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
            }
            else
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem("x"));
            }
        }
    }
    for (int i = 0; i<9; i++)
    {
        for (int j = 0; j<9; j++)
        {
            ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            QString str=ui->tableWidget->item(i,j)->text();
            int num=str.toInt();
            grid[i][j]=num;
        }
    }

}

//检查初盘的合法性
void Widget::on_pushButton_5_clicked()
{
    f=false;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            QString str=ui->tableWidget->item(i,j)->text();
            int num=str.toInt();
            grid[i][j]=num;
        }
    }
    bool c=true;
    dfs(grid,0,0);
    if(f==true)
    {
        QMessageBox msgBox;
         msgBox.setText("输入合法");
         f=false;
         msgBox.setStandardButtons(QMessageBox::Ok);
         msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
         msgBox.setText("输入不合法");
         msgBox.setStandardButtons(QMessageBox::Ok);
         msgBox.exec();
    }

}

//递归求解问题
void dfs(int grid[][9],int i,int j)
{
    if(i==9)
    {
            f=true;
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    ans[i][j]=grid[i][j];
                }
            }
        return;
    }
    if(f==false)
    {
        if(grid[i][j]==1||grid[i][j]==2||grid[i][j]==3||grid[i][j]==4||grid[i][j]==5||grid[i][j]==6||grid[i][j]==7||grid[i][j]==8||grid[i][j]==9)
     {
        if(j<8)
        {
            dfs(grid,i,j+1);
        }
        else
        {
            dfs(grid,i+1,0);
        }
    }
    else
    {
        for (int k = 1; k <= 9; k++)
                {
                    if (isTrue(grid,i, j, k))
                    {
                        if (j < 8 && !grid[i][j])
                        {
                            grid[i][j] = k;
                            dfs(grid,i, j + 1);
                            grid[i][j] = 0;
                        }
                        else if (j == 8 && !grid[i][j])
                        {
                            grid[i][j] = k;
                            dfs(grid,i + 1, 0);
                            grid[i][j] = 0;
                        }
                    }
                }
        }
    }
    return;
}

//调用dfs搜索函数，获取答案
void Widget::on_pushButton_6_clicked()
{
    dfs(grid,0,0);
    if(select==0)
    {
        if(f==true)
        {
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(ans[i][j])));
                     ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                }
            }
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    int t=arr[RandomNumber][i][j];
                    if(t<10)
                    {
                        ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(arr[RandomNumber][i][j])));
                        ui->tableWidget->item(i, j)->setForeground(Qt::red);
                         ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                         QTableWidgetItem* pItem = ui->tableWidget->item(i, j);
                         pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
                    }
                }
            }
        }
        else
        {
            QMessageBox msgBox;
             msgBox.setText("输入不合法,无解");
             msgBox.setStandardButtons(QMessageBox::Ok);
             msgBox.exec();
        }
    }
    else
    {
        if(f==true)
        {
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(ans[i][j])));
                     ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                }
            }
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    int t=sel1[i][j];
                    if(t==1)
                    {
                        ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(grid[i][j])));
                        ui->tableWidget->item(i, j)->setForeground(Qt::red);
                         ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                         QTableWidgetItem* pItem = ui->tableWidget->item(i, j);
                         pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
                    }
                }
            }
        }
        else
        {
            QMessageBox msgBox;
             msgBox.setText("输入不合法,无解");
             msgBox.setStandardButtons(QMessageBox::Ok);
             msgBox.exec();
        }
    }
    f=false;
}

//人工设置初盘
void Widget::on_pushButton_4_clicked()
{
    select=1;
    ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem("x"));
            grid[i][j]=0;
            ui->tableWidget->item (i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

}

//取消棋盘锁定，开始游戏
void Widget::on_pushButton_7_clicked()
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    if(select==1)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                QString str=ui->tableWidget->item(i,j)->text();
                int num=str.toInt();
                if(num==1||num==2||num==3||num==4||num==5||num==6||num==7||num==8||num==9)
                {
                    sel1[i][j]=1;
                }
            }
        }
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            QString str=ui->tableWidget->item(i,j)->text();
            int num=str.toInt();
            grid[i][j]=num;
            if(grid[i][j]==1||grid[i][j]==2||grid[i][j]==3||grid[i][j]==4||grid[i][j]==5||grid[i][j]==6||grid[i][j]==7||grid[i][j]==8||grid[i][j]==9)
            {
                ui->tableWidget->item(i, j)->setForeground(Qt::red);
                QTableWidgetItem* pItem = ui->tableWidget->item(i, j);
                pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
            }
        }
    }
}
