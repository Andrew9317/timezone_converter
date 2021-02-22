#ifndef MAINFORM_HPP
#define MAINFORM_HPP

#include "RoundedDialog.hpp"

class MainForm : public RoundedDialog
{
    Q_OBJECT

    QWidget* createTimeFrameToggleWidget();

  public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm() = default;

  signals:
    void sigTimeSelected();
    void sigFrameSelected();
};

#endif