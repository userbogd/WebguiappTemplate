const app = Vue.createApp({
	data() {
		return {
			slvdevices: [],
			slvdevices2: [],
			selecteddevs: [],
			sliderdata: [
				{ id: 0, name: 'ch1', val: 0, min: 0, max: 255 },
				{ id: 1, name: 'ch2', val: 2, min: 0, max: 255 },
				{ id: 2, name: 'ch3', val: 4, min: 0, max: 255 },
				{ id: 3, name: 'ch4', val: 8, min: 0, max: 255 },
				{ id: 4, name: 'ch5', val: 16, min: 0, max: 255 },
				{ id: 5, name: 'ch6', val: 32, min: 0, max: 255 },
				{ id: 6, name: 'ch7', val: 64, min: 0, max: 255 },
				{ id: 7, name: 'ch8', val: 128, min: 0, max: 255 },
				{ id: 8, name: 'ch9', val: 255, min: 0, max: 255 }
			],
			sliderdata2: [
				{ id: 9, name: 'ch1', val: 255, min: 0, max: 255 },
				{ id: 10, name: 'ch2', val: 128, min: 0, max: 255 },
				{ id: 11, name: 'ch3', val: 64, min: 0, max: 255 },
				{ id: 12, name: 'ch4', val: 32, min: 0, max: 255 },
				{ id: 13, name: 'ch5', val: 16, min: 0, max: 255 },
				{ id: 14, name: 'ch6', val: 8, min: 0, max: 255 },
				{ id: 15, name: 'ch7', val: 4, min: 0, max: 255 },
				{ id: 16, name: 'ch8', val: 2, min: 0, max: 255 },
				{ id: 17, name: 'ch9', val: 0, min: 0, max: 255 }
			]
		}
	}
});

app.component('onesl', {
	props: ["onesldat"],
	methods: {
		SliderChange() {

		},
		InputChange() {

		}
	},
	template: `<div class="channel"><label class="chnam">{{onesldat.name}}</label>		
		    <input class="rngval" type="range" :id="onesldat.id" :value="onesldat.val" :min="onesldat.min" :max="onesldat.max" v-on:change="SliderChange"\>
		    <input class="inpval" type="number" :id="onesldat.id" :value="onesldat.val" :min="onesldat.min" :max="onesldat.max" v-on:change="InputChange"\></div>`
});


app.component('sliders', {
	data() {
		return {

			chnum: 4
		}
	},

	props: ["sldat"],
	methods: {

	},
	template: `<div class="sliders">
		    	<onesl v-for="sld in sldat"  :onesldat="sld"></onesl>	
		               </div>`
});

app.component('svldetails', {
	props: ["slvdev"],
	methods: {
		SelDev() {
			this.slvdev.sel = !this.slvdev.sel;
		}
	},
	template: `<div class="svldetails" :class="{ selection: slvdev.sel}" v-on:click="SelDev">
							<p>{{slvdev.type}}</p>
		                    <p>{{slvdev.addr}}</p>
		                </div>`
});
app.component('devlist', {
	data() {
		return {
			devtypes: [
				{ type: 'RGBW', chls: ["RED", "GREEN", "BLUE", "WHITE"] },
				{ type: 'RGB', chls: ["RED", "GREEN", "BLUE"] },
				{ type: 'D', chls: ["CH1"] },
				{ type: 'DIMMER', chls: ["CH1", "CH2", "CH3", "CH4", "CH5", "CH6", "BRIGHT", "GAMMA", "SCENE"] }
			],
			selectedtype: 'RGB',
			addrforadd: 1
		}
	},
	props: ["slvdevices", "key"],

	methods:
	{
				
		AddDevice() {
			this.slvdevices.push({ type: this.selectedtype, addr: this.addrforadd, sel: false });
			for (i = 0; i < this.devtypes.length; i++)
				if (this.devtypes[i].type == this.selectedtype)
					this.addrforadd += this.devtypes[i].chls.length;
		},
		DelDevice() {
			for (i = 0; i < this.slvdevices.length; i++) {
				while (this.slvdevices[i].sel == true)
					this.slvdevices.splice(i, 1);
			}
		},
		PostData() {
					
			//uuid = uuidv4();
	  		time = new Date().toISOString();
	  		var mess = { data:{}};
	  		mess.data.msgid = Math.floor(Date.now()/1000);
	  		mess.data.time = time;
	  		mess.data.msgtype = 1;
	  		mess.data.payloadtype = 1;
	  		var pload  = {};
			pload.devices = this.slvdevices;
			mess.data.payload = pload;
			//var hash = crypto.sha256.hmac.create(GetVal("shakey"));
	  		//hash.update(JSON.stringify(mess.data));
	  		//mess.signature = (hash.hex()).toUpperCase();
			mess.signature = "123";
			fetch("/api", {
				method: 'post',
				headers: { "Content-type": "application/json" },
				body: JSON.stringify(mess)
			});
		}
	},
	computed: {
		selected: function() {
			this.selecteddevs = this.slvdevices.filter(function(n) {
				return this.slvdevices[n].sel;
			})
		}
	},
	template: `<div>
		    		<button class="btn" v-on:click="AddDevice">Add device</button>
		    		<select v-model="selectedtype">
		            <option v-for="dtype in devtypes" v-bind:value="dtype.type">{{dtype.type}}</option>
		       		</select>
		       		<input v-model="addrforadd" type="number"/>
		    	  	<div class="container">
		    		<svldetails v-for="slvdev in slvdevices" :key="slvdev.id" :slvdev="slvdev"></svldetails>
		            </div>
		            <button class="btn" v-on:click="DelDevice">Delete device</button>
		            <button class="btn" v-on:click="PostData">Save conf</button>
					</div>`
});
app.mount('#app');
