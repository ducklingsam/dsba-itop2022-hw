#include "pokechar.h"
#include "ui_pokechar.h"
#include "addwindow.h"
#include "pokeinfo.h"
#include "includesAndStd.h"

pokeChar::pokeChar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pokeChar)
{
    ui->setupUi(this);
    createTable();
    proxyModel = new class proxyModel();
    proxyModel -> setSourceModel(model);
    ui->nameTable->setModel(proxyModel);
    ui->nameTable->setSortingEnabled(true);
    ui->nameTable->sortByColumn(1, Qt::SortOrder::AscendingOrder);
}

pokeChar::~pokeChar()
{
    delete ui;
}

map<string, int> cntTypes(vector<Pokemon> p) {
    map<string, int> types;
    for (int i = 0; i < p.size(); i++) {
        if (p[i].ftype != "") {
            map<string, int>::iterator it(types.find(p[i].ftype));
            if (it != types.end()) {
                it->second++;
            } else {
                types[p[i].ftype] = 1;
            }
        }
    }
    for (int i = 0; i < p.size(); i++) {
        if (p[i].stype != "") {
            map<string, int>::iterator it(types.find(p[i].stype));
            if (it != types.end()) {
                it->second++;
            } else {
                types[p[i].stype] = 1;
            }
        }
    }
    for (auto it = types.begin(); it != types.end(); it++) {
        std::cout << it->first << " " << it->second << '\n';
    }
    return types;
}

void pokeChar::info(vector<Pokemon> p) {
    infomod = new QStandardItemModel(0, 2, this);
    infomod->setHorizontalHeaderItem(0, new QStandardItem("Type"));
    infomod->setHorizontalHeaderItem(1, new QStandardItem("Amount"));
    ui->tableView->setModel(infomod);
    map<string, int> types = cntTypes(p);
    int cnt = 0, total = 0;
    for (auto it = types.begin(); it != types.end(); it++) {
        infomod->insertRow(cnt);
        infomod->setData(infomod->index(cnt,0), QString::fromStdString(it->first));
        total += it->second;
        infomod->setData(infomod->index(cnt, 1), QString::number(it->second));
        cnt++;
    }
    ui->ta->setText(QString::number(p.size()));
}

void pokeChar::createTable() {
    bool flag = false;

    // preparing treeView for data
    model = new QStandardItemModel(0, 0, this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    QString fileName = QFileDialog::getOpenFileName(this, "Select a file to open...", "/", "(*.csv)");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    file.readLine();
    // reading .csv and pass it to the struct Po vector
    while(!file.atEnd()) {
        string token;
        string line = file.readLine().toStdString();
        istringstream ss(line);
        vector<string> lineAsVector;
        while(getline(ss, token, ',')) lineAsVector.push_back(token);
        Pokemon po;
        po.number = stoi(lineAsVector[0]);
        po.name = lineAsVector[1];
        po.ftype = lineAsVector[2];
        po.stype = lineAsVector[3];
        po.cp = stoi(lineAsVector[4]);
        po.hp = stoi(lineAsVector[5]);
        if (!lineAsVector[6].empty() && lineAsVector[6][lineAsVector[6].length()-1] == '\n') {
            lineAsVector[6].erase(lineAsVector[6].length()-1);
        }
        po.url = lineAsVector[6];
        p.push_back(po);
    }

    file.close(); // close the file

    // insert parsed data to the treeView
    for (int i = 0; i < p.size(); i++) {
        model->insertRow(i);
        model->setData(model->index(i, 0), QString::fromStdString(p[i].name));
    }

    info(p);
}

void pokeChar::on_mainButton_clicked()
{
    // warn the user about the consequences
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Are you sure you want to quit?");
    msgBox.setInformativeText("All unsaved data will be deleted!");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    msgBox.setPalette(pal);

    int ans = msgBox.exec(); // get the answer of the user

    switch(ans) {
        case QMessageBox::Yes: {
            this->close();
            break;
        }
        case QMessageBox::No: {
            break;
        }
    }
}


void pokeChar::on_addButton_clicked()
{
    addWindow add;
    Pokemon newPoke;
    this->p.push_back(newPoke);
    add.setModelPointer(&p[p.size() - 1], model);
    add.setModal(true);
    add.exec();
    for (int i = 0; i < p.size(); i++) {
        std::cout << p[i].name << '\n';
    }
    info(p);
}

void pokeChar::on_deleteButton_clicked()
{
    int selectedRow = ui->nameTable->currentIndex().row();
    this->model->removeRows(selectedRow, 1);
    vector<Pokemon>::iterator it = this->p.begin() + selectedRow;
    this->p.erase(it);
    info(p);
}

// put details of the pokemon into labels
void pokeChar::on_nameTable_clicked(const QModelIndex &index)
{
    string pokemonName = (index.data().toString()).toStdString();
    string url = "No URL added";
    for (int i = 0; i < p.size(); i++) {
        if (p[i].name == pokemonName) {
            ui->num->setText(QString::number(p[i].number));
            ui->ftype->setText(QString::fromStdString(p[i].ftype));
            ui->stype->setText(QString::fromStdString(p[i].stype));
            ui->cp->setText(QString::number(p[i].cp));
            ui->hp->setText(QString::number(p[i].hp));
            if (p[i].url != "") { // there is no option to paste link into new pokemons, check link avability
                url = string("<a href=\"") + p[i].url + string("\">Click Here</a>");
                ui->url->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
                ui->url->setOpenExternalLinks(true);
                ui->url->setTextFormat(Qt::RichText);
            }
            ui->url->setText(QString::fromStdString(url));
        }
    }
}

// update button creates new .csv file and puts updated info about quantity
void pokeChar::on_updateButton_clicked()
{
    updDir = QFileDialog::getSaveFileName(nullptr, "updData", "/", "CSV (*.csv)");

    QFile file(updDir); //create new file
    // parse from vector to .csv
    if (file.open(QFile::WriteOnly|QFile::Text)) {
        QTextStream stream(&file);
        stream << "Pokemon No.," << "Name," << "Type 1," << "Type 2," << "Max CP," << "Max HP," << "Image URL\n";
        for (int i = 0; i < p.size(); i++) {
            stream << p[i].number << ',' << QString::fromStdString(p[i].name) << ',' << QString::fromStdString(p[i].ftype) << ',' << QString::fromStdString(p[i].stype)
                   << ',' << p[i].cp << ',' << p[i].hp << ',' << QString::fromStdString(p[i].url) << '\n';
        }
    }
}

// deletes updated dataset
void pokeChar::on_resetButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("This dataset will be deleted");
    msgBox.setInformativeText("Are you sure you want to proceed?\nYou will be returned to the main window");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    msgBox.setPalette(pal);

    int ans = msgBox.exec();
    switch(ans) {
        case QMessageBox::Yes: {
            QFile file(updDir);
            file.remove();
            this->close();
            break;
        }
        case QMessageBox::No: {
            break;
        }
    }
}

