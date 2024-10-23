#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QProcess>

class AssetManager : public QWidget {
public:
    AssetManager(QWidget *parent = 0);

private slots:
    void uploadAsset();

private:
    QPushButton *uploadButton;
};

AssetManager::AssetManager(QWidget *parent) : QWidget(parent) {
    uploadButton = new QPushButton("Upload Asset", this);
    connect(uploadButton, &QPushButton::clicked, this, &AssetManager::uploadAsset);

    uploadButton->setGeometry(50, 50, 150, 50);
}

void AssetManager::uploadAsset() {
    QString fileName = QFileDialog::getOpenFileName(this, "Upload Asset", "", "All Files (*)");
    if (!fileName.isEmpty()) {
        // Add file to version control (Git)
        QProcess git;
        git.start("git", QStringList() << "add" << fileName);
        git.waitForFinished();

        QMessageBox::information(this, "Success", "Asset uploaded and added to version control.");
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AssetManager manager;
    manager.setWindowTitle("Game Asset Manager Tool");
    manager.show();

    return app.exec();
}
