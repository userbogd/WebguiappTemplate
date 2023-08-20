import { Dialog } from "quasar";

function secondsToHms(d) {
  d = Number(d);
  var dd = Math.floor(d / 86400);
  var h = Math.floor(d % 86400 / 3600);
  var m = Math.floor(d % 3600 / 60);
  var s = Math.floor(d % 3600 % 60);
  return (' ' + dd + 'd ' + (h < 10 ? "0" : "") + h + ":" + (m < 10 ? "0" : "") + m + ":" + (s < 10 ? "0" : "") + s);
}

function ShowDelayDialog(mess, time, onexpire) {
  const dialog = Dialog.create({
    message: '',
    progress: true,
    persistent: true, // we want the user to not be able to close it
    ok: false // we want the user to not be able to close it
  })

  let percentage = 0
  const interval = setInterval(() => {
    percentage = Math.min(100, percentage + 10000 / time);
    dialog.update({ message: `${mess} ${percentage}%` })


    // if we are done, we're gonna close it
    if (percentage === 100) {
      clearInterval(interval)
      setTimeout(() => {
        dialog.hide();
        onexpire();
      }, 350)
    }
  }, 100)
}

export { secondsToHms, ShowDelayDialog }
