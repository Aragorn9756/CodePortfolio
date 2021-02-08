window.addEventListener("load", addListeners)

/***add variables***/
var captions = new Array ("Samus Aran is not a robot, but rather a woman in"
	+ " a high-tech alien powersuit.", "Although the in-game sprite for Samus is "
	+ "rather rudimentary in the original <span>Metroid</span>, her suit really "
	+ "hasn't changed drastically from the original design, pictured right.", 
	"Due to memory constraints in the GameBoy, <span>Metroid 2: Return of "
	+ "Samus</span> relied on visual detail rather than color for Samus' suit."
	+ " This is where Samus' iconic shoulder pads originate.", "<span>Super "
	+ "Metroid</span> is Samus at her most iconic point in history. This game would"
	+ " lay the groundwork for every game that followed.", "In <span>Metroid "
	+ "Fusion</span>, Samus succumbs to a parasite. The vaccine causes parts of"
	+ " her suit to fuse to her body, effectively creating a new suit (shown "
	+ "left). Another parasite mimicing Samus' original suit, nicknamed the "
	+ "SA-X (right), hunts Samus down.", "<span>Metroid Prime</span> was not"
	+ " only Samus' first 3-d outing, but also was in a first-person perspective."
	+ " This was the Metroid gamers didn't even know they wanted.", "At the very "
	+ "end of <span>Metroid Prime</span> Samus is forced to harness the highly "
	+ "radioactive and powerful substance, phazon, in order to take out the parasitic "
	+ "Metroid Prime, also under the influence of phazon", "<span>Metroid: "
	+ "Zero Mission</span> was a remake of the orignial <span>Metroid</span>.", 
	"<span>Zero Mission</span> also introduced Samus playable without her suit, "
	+ "called the \"Zero Suit\".", "<span>Metroid Prime 2: Echoes</span> introduced "
	+ "players to the planet Aether. Aether was split into to dimensions battling for "
	+ "control, the dark and the light. Towards the end of the game, Samus gained the "
	+ "Dark Suit, which allowed her to traverse the dark dimension without negative "
	+ "side affects, and the Light Suit at the very end, giving her complete power over "
	+ "the dark dimension.", "The surprise final boss of <span>Echoes</span>, Dark "
	+ "Samus is a purely destructive entity formed from Samus' cast-off Phazon suit "
	+ "of the previous game.", "After being poisoned with phazon by dark Samus at "
	+ "the beginning of the game, Samus' hazard suit of <span>Metroid Prime 3: "
	+ "Corruption</span> is the only thing that keeps the phazon at bay as she "
	+ "races to take out Dark Samus once and for all.", "In the highly divisive "
	+ "<span>Metroid: Other M</span>, Samus get's her first voice-over as well as "
	+ "a backstory not all fans appreciated.", "After a seven year hiatus, Samus"
	+ " finally comes back in full force with <span>Metroid: Samus Returns</span>, the "
	+ "long awaited remake of <span>Metroid 2</span>.", "With the beginning of "
	+ "development announced the same day as <span>Samus Returns</span>, Metroid "
	+ "fans around the world are hotly anticipating <span>Metroid Prime 4</span>, "
	+ "the Metroid game they have been waiting over 10 years to get their hands on.")

var images = new Array ("images/Metroid_opt.jpg", 
	"images/orig_metroid_opt.jpg", "images/metroid_2_opt.jpg",
	"images/super_metroid_opt.png", "images/fusion_opt.jpg", "images/prime1_opt.jpg",
	"images/prime_phazon_suit_opt.png", "images/zero_mission_varia_suit.gif", 
	"images/zero_suit.gif", "images/prime_2_suits_opt.jpg",
	"images/prime_dark_samus_opt.jpg", "images/prime_3_hazard_suit_opt.jpg",
	"images/other_m_varia_opt.jpg", 
	"images/samus_returns_opt.jpg", "images/prime_4_opt.jpg")

var slide_titles = new Array ("Meet Samus Aran, Bounty Hunter", "The Beginning "
	+ "of a Juggernaut", "Palette Down, Detail Up", "The Infamous Classic",
	"Parsites! Why'd it have to be Parasites!", "Taking the Next Step", 
	"Fighting Fire with Fire", "Back to the Roots...", "...And then Some",
	"A Study of Duality", "For Each Light, There is a Dark", 
	"Down, but Certainly Not Out", "One Step Forward, Two Steps Back", 
	"A Return to Form", "The One We Didn't Dare Hope For")
	
var index = 0
var timer

function addListeners () {
	document.getElementById("previous").addEventListener("click", previousImage)
	document.getElementById("next").addEventListener("click", nextImage)
	document.getElementById("play").addEventListener("click", playSlideShow)
	document.getElementById("pause").addEventListener("click", function(){clearInterval(timer)})
}

function nextImage () {
	index++
	if (index === images.length) {
		index = 0
	}
	document.getElementById("slide_title").innerHTML = slide_titles[index]
	document.getElementById("image").src = images[index]
	document.getElementById("caption").innerHTML = captions[index]
}

function previousImage () {
	index--
	if (index === -1) {
		index = images.length - 1
	}
	document.getElementById("slide_title").innerHTML = slide_titles[index]
	document.getElementById("image").src = images[index]
	document.getElementById("caption").innerHTML = captions[index]
}

function playSlideShow() {
	clearInterval(timer)
	timer = setInterval("nextImage()", 10000)
}