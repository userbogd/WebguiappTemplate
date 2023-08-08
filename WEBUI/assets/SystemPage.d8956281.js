import{S as y,W as i,X as v,Y as a,ac as b,Z as t,ad as d,a3 as n,aR as u,a2 as c,aS as p,$ as f,aT as g,a as S,a0 as q,o as $,T as k,a4 as C}from"./index.7dcc8469.js";import{S as l}from"./network.2d97c5c2.js";import"./axios.d8b50f6e.js";const x=n("div",{class:"text-h6"},"SYSTEM",-1),V={class:"q-pa-md"},h={class:"q-gutter-md q-pa-none q-pb-none"},I=Object.assign({name:"SystemCard"},{__name:"SystemCard",setup(_){const e=y({net_bios_name:"",sys_name:"",sys_pass:""});return l(e,2,0,"mykey"),(r,s)=>(i(),v(b,{flat:"",bordered:"",class:"card"},{default:a(()=>[t(d,null,{default:a(()=>[x]),_:1}),t(d,{class:"q-pt-none"},{default:a(()=>[n("div",V,[n("div",h,[t(u,{dense:!0,modelValue:e.net_bios_name,"onUpdate:modelValue":s[0]||(s[0]=o=>e.net_bios_name=o),label:"Device bios name"},null,8,["modelValue"]),t(u,{dense:!0,modelValue:e.sys_name,"onUpdate:modelValue":s[1]||(s[1]=o=>e.sys_name=o),label:"User name"},null,8,["modelValue"]),t(u,{dense:!0,modelValue:e.sys_pass,"onUpdate:modelValue":s[2]||(s[2]=o=>e.sys_pass=o),label:"User password"},null,8,["modelValue"])])])]),_:1}),t(g,null,{default:a(()=>[t(c,{flat:"",onClick:s[3]||(s[3]=o=>p(l)(e,1,0,"mykey"))},{default:a(()=>[f("Apply")]),_:1}),t(c,{flat:"",onClick:s[4]||(s[4]=o=>p(l)(e,1,1,"mykey"))},{default:a(()=>[f("Save")]),_:1}),t(c,{flat:"",onClick:s[5]||(s[5]=o=>p(l)(e,1,2,"mykey"))},{default:a(()=>[f("Save&Reboot")]),_:1})]),_:1})]),_:1}))}}),w=n("div",{class:"text-h6"},"FIRMWARE",-1),O={class:"q-pa-md"},U={class:"q-gutter-md q-pa-none q-pb-none"},B={class:"text-subtitle2"},Q=Object.assign({name:"FirmwareCard"},{__name:"FirmwareCard",setup(_){const e=y({time:0});l(e,2,0,"mykey");const r=S({get(){return new Date(e.time*1e3).toISOString()}});return(s,o)=>(i(),v(b,{flat:"",bordered:"",class:"card"},{default:a(()=>[t(d,null,{default:a(()=>[w]),_:1}),t(d,{class:"q-pt-none"},{default:a(()=>[n("div",O,[n("div",U,[n("div",B,q(r.value),1)])])]),_:1})]),_:1}))}}),R=n("div",{class:"text-h6"},"INFO",-1),j={class:"q-pa-md"},A={class:"q-gutter-md q-pa-none q-pb-none"},D={class:"text-subtitle2"},F=Object.assign({name:"StatCard"},{__name:"StatCard",setup(_){const e=y({time:0});l(e,2,0,"mykey");let r;$(()=>{r=setInterval(()=>{l(e,2,0,"mykey")},1e3)}),k(()=>clearInterval(r));const s=S({get(){return new Date(e.time*1e3).toISOString()}});return(o,T)=>(i(),v(b,{flat:"",bordered:"",class:"card"},{default:a(()=>[t(d,null,{default:a(()=>[R]),_:1}),t(d,{class:"q-pt-none"},{default:a(()=>[n("div",j,[n("div",A,[n("div",D,q(s.value),1)])])]),_:1})]),_:1}))}}),N={class:"q-pa-md row items-start q-gutter-md"},W=Object.assign({name:"SystemPage"},{__name:"SystemPage",setup(_){return(m,e)=>(i(),C("div",N,[t(I),t(Q),t(F)]))}});export{W as default};
