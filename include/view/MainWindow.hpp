#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "controller/GameController.hpp"

// Inheriting from QMainWindow means this parent will be responsible
// for killing all children
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onHigherButtonClicked();
    void onLowerButtonClicked();
    void onResetButtonClicked();
    void onHowToPlayClicked();

private:
    // Game controller (business logic)
    GameController controller_;

    // UI components
    QLabel *currentCardLabel_;
    QLabel *scoreLabel_;
    QLabel *activePlayerLabel_;
    QLabel *messageLabel_;
    QPushButton *higherButton_;
    QPushButton *lowerButton_;
    QPushButton *resetButton_;
    QPushButton *howToPlayButton_;

    // UI updates
    void updateUI();
    void setupUI();
    void showFeedback();
    QString formatCardForDisplay(const std::string &cardStr) const;
};

#endif
