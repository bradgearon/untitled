import QtQuick 2.0
import QtQuick.Controls 2.0
import QtWebView 1.1

ApplicationWindow {
    property var viewModel
    property string initialUrl

    WebView {
        id: webView
        anchors.fill: parent
        url: initialUrl
        onUrlChanged: function (progress) {
            var baseUrl = initialUrl.replace('index.html', '');
            webView.runJavaScript("
             var $rs = angular.element(document.body).scope().$root;
              $rs.$apply(function() {
                  $rs.baseUrl = '" + baseUrl + "';
              });
        ");
            viewModel.loaded();
            console.log("loaded " + webView.url);
        }
        onLoadingChanged: function (loadRequest) {
            if(loadRequest.status !==  WebView.LoadStartedStatus) {
                return;
            }

            var url = (loadRequest.url + '').toLowerCase();
            console.log('on loadingChanged: ' + url);

            if(url.lastIndexOf('action') < 0) {
                return;
            }

            if(url.lastIndexOf('close') > 0) {
                webView.url = initialUrl;
                console.log('closing');
                viewModel.close();
                return;
            }

            if(url.lastIndexOf('read') > 0) {
                webView.url = initialUrl;
                console.log('read');
                var readUrl = decodeURIComponent(url.substring(url.lastIndexOf('url=') + 4));
                console.log(readUrl);
                viewModel.read();
                return;
            }
        }
    }
}
