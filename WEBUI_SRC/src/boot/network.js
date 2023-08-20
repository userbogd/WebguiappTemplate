import { api } from "boot/axios";
import { sha256 } from "js-sha256";
import { Notify, Dialog } from "quasar";

const API_URL = "/api";
const SHA256_HMAC_KEY = "mykey";

function ShowSaveDialog(apltype) {
  const opername = ['Data applying...', 'Data saving...', 'Data saving and reboot...'];
  let step = (apltype == 2) ? 1 : 10;
  let percentage = 0;
  const dialog = Dialog.create({ message: opername[apltype], progress: true, persistent: true, ok: false })
  const interval = setInterval(() => {
    percentage = Math.min(100, percentage + step);
    dialog.update({
      message: `${opername[apltype]} ${percentage}%`
    })
    if (percentage === 100) {
      clearInterval(interval);
      setTimeout(() => { dialog.hide() }, 350)
    }
  }, 100)
}



function PostData(varlist, messtype, applytype, onfinished) {
  var pld = {};
  var data = {};
  data.msgid = Math.floor(Date.now() / 1000);
  data.time = new Date().toISOString();
  data.msgtype = messtype;
  data.payloadtype = 1;
  data.payload = {};
  data.payload.applytype = applytype;
  data.payload.variables = varlist;
  pld.data = data;
  pld.signature = sha256.hmac(SHA256_HMAC_KEY, JSON.stringify(data));

  api
    .post(API_URL, JSON.stringify(pld), {
      headers: { "Content-Type": "application/json" },
    })
    .then((response) => {
      var resp = response.data.data.payload.variables;
      for (var k in resp) varlist[k] = resp[k];
      if (onfinished) onfinished();
    })
    .catch((err) => {
      Notify.create({ color: "negative", position: "top", message: err.message, icon: "report_problem", });
    });

}

function SendAndRequest(varlist, mstp, apltp, shakey, okreport) {
  var onfinish = (okreport) ? () => { ShowSaveDialog(apltp) } : null;
  PostData(varlist, mstp, apltp, onfinish);
}

export { SendAndRequest, PostData };




