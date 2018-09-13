#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;
MainWindow::MainWindow(QWidget *parent) :source(true),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    map<string,int> airport = r.getAirportList();

    setUpWebEnginer();
    for(const auto &x: airport)
    {
//        QString line = "addAirportMarker(" + QString::number(r.getAirport(x.second).lat)
//                + "," +QString::number(r.getAirport(x.second).lon)
//                + "," +QString::fromStdString(r.getAirport(x.second).name) + ");";
        ui->sourceBox->addItem(QString::fromStdString(x.first));
        ui->DestinationBox->addItem(QString::fromStdString(x.first));
//        view->page()->runJavaScript(line);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_compute_clicked()
{
    string flight;
    r.showPath( ui->sourceBox->currentText().toStdString(), ui->DestinationBox->currentText().toStdString());
    view->page()->runJavaScript("clear();");
    auto x = r.getPath(ui->sourceBox->currentText().toStdString(), ui->DestinationBox->currentText().toStdString());
    while(!x.empty())
    {                   //pin markers on each connecting airport
        vertex v = x.top();
        x.pop();
        double sourceLat = r.getAirport(v.source).lat;
        double sourceLon = r.getAirport(v.source).lon;
        double destinationLat = r.getAirport(v.destination).lat;
        double destinationLon = r.getAirport(v.destination).lon;
        string source = r.getAirport(v.source).name;
        string destination = r.getAirport(v.destination).name;
        QString line = "addCoord(";
        if(v.source == r.getAirportID(ui->DestinationBox->currentText().toStdString()))
        {
            view->page()->runJavaScript(line + QString::number(destinationLat) + "," + QString::number(destinationLon) +");");
            view->page()->runJavaScript(line + QString::number(sourceLat) + "," + QString::number(sourceLon) +");");
        }
        else
            view->page()->runJavaScript(line + QString::number(destinationLat) + "," + QString::number(destinationLon) +");");
        //setting the text of list of connect filght
        flight = flight+"From "+ r.getAirport(v.destination).name+"("+r.getAirport(v.destination).city + ") to "
                + r.getAirport(v.source).name+"("+r.getAirport(v.source).city + ") for "
                + to_string(int(floor(v.weight+ 0.5))) + " miles\n"
                + "via:";
        for(auto x: r.getEdges(v.source))
            if(v.destination == x.destination)
                if (r.getAirline(x.airlineCode).name != "")
                flight = flight+ "\n\t" + "  " + r.getAirline(x.airlineCode).name + " Airlines";
        flight = flight + "\n\n";
    }
    ui->textBrowser->setText(QString::fromStdString(flight));
    view->page()->runJavaScript("plotPoints();");

}

void MainWindow::setUpWebEnginer()
{
     view = new QWebEngineView;
     channel = new QWebChannel(view->page());
     view->page()->setWebChannel(channel);
     channel->registerObject("mainWindow",this);
     QUrl url = QUrl("qrc:/map.html");
     ui->verticalLayout_3->addWidget(view);
     view->page()->load(url);

}

void MainWindow::Update(const QString &airportName)
{
    if(source)
    {
        ui->sourceBox->setCurrentText(airportName.toStdString().c_str());
        source = false;
    }
    else{
        ui->DestinationBox->setCurrentText(airportName.toStdString().c_str());
        source = true;
    }
}
