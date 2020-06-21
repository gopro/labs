(function () {
  if (navigator.serviceWorker) {
    const REPO_NAME = 'gopro-labs';
    navigator.serviceWorker.register(`/${REPO_NAME}/service-worker.js`, { scope: `/${REPO_NAME}/` })
  }
})()
