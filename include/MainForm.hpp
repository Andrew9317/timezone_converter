#include <QMainWindow>

class MainForm : public QMainWindow
{
    Q_OBJECT

    QWidget* createTimeFrameToggleWidget();
    
public:
    MainForm(QWidget* parent = nullptr);
    ~MainForm() = default;

signals:
    void sigTimeSelected();
    void sigFrameSelected();
};