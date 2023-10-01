#include <QApplication>
#include <QBuffer>
#include <QDir>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWebEngineProfile>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlScheme>
#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineView>

QString websiteBasePath() {
    QDir path = QApplication::applicationDirPath();
    path.cdUp();
    return path.path() + "/website/";
}

class bresHandler : public QWebEngineUrlSchemeHandler {
public:
    explicit bresHandler(QObject *parent = nullptr) {};

    void requestStarted(QWebEngineUrlRequestJob *job) override {
        const QByteArray method = job->requestMethod();
        const QUrl url = job->requestUrl();

        if (method == QByteArrayLiteral("GET")) {
            job->reply(QByteArrayLiteral("image/png"), makeReply(url));
        }
    }

    static QIODevice *makeReply(const QUrl &url) {
        QString picPath = websiteBasePath() + url.toString().split("://")[1];
        qDebug() << "load <" << picPath;
        QFile f = QFile(picPath);
        if (!f.open(QIODevice::ReadOnly)) {
            qDebug() << "nofile";
            return {};
        }
        auto *imgBytes = new QByteArray(f.readAll());
        auto *buf = new QBuffer(imgBytes);
        return buf;
    }
};

int main(int argc, char *argv[]) {

    QWebEngineUrlScheme customUrlHandler("bres");
    customUrlHandler.setFlags(QWebEngineUrlScheme::SecureScheme | QWebEngineUrlScheme::LocalScheme
                              | QWebEngineUrlScheme::LocalAccessAllowed | QWebEngineUrlScheme::CorsEnabled);
    QWebEngineUrlScheme::registerScheme(customUrlHandler);

    QApplication a(argc, argv);

    auto *handler = new bresHandler();
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("bres", handler);

    auto *view = new QWebEngineView();
    view->setFixedSize(1600, 900);
    QDir path = QApplication::applicationDirPath();
    path.cdUp();
    QString webpagePath = "file://" + websiteBasePath() + "index.html";

    qDebug() << webpagePath;;
    QUrl b1 = QUrl(webpagePath);

    view->load(b1);

    auto *layout = new QVBoxLayout();
    layout->addWidget(view);
    auto *container = new QWidget;
    container->setLayout(layout);
    container->show();

    return QApplication::exec();
}