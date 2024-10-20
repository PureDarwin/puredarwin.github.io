const startTime = Date.now();
let count = 0;

const { readdirSync, lstatSync, writeFileSync } = require("fs");
const { join } = require("path");

function loop(path) {
	let files = readdirSync(path);
	let c = "";
	files.sort((a, b) => {
		a = a.toLowerCase();
		b = b.toLowerCase();
		if (a.startsWith("_") && !b.startsWith("_")) return -1;
		if (b.startsWith("_") && !a.startsWith("_")) return 1;
		return a < b ? -1 : a == b ? 0 : 1;
	});
	files.forEach((file) => {
		let fullPath = join(path, file);
		const lastDotIndex = file.lastIndexOf(".");
		file != "_sidebar.md" && file != "_navbar.md" && (c += `- [${file.substring(file.indexOf("_") + 1, lastDotIndex > 0 ? lastDotIndex : file.length)}](${encodeURI("/" + fullPath)})\n`);
		count += 1;
		if (lstatSync(fullPath).isDirectory()) {
			let s = loop(fullPath);
			s.split(/(?<=\r?\n)/).forEach((line) => {
				c += `	${line}`;
			});
		}
	});

	return c;
}

const dirs = { "about": "About", "developers": "Developers", "users": "Users", "news": "News" };
for (const [dir, name] of Object.entries(dirs)) {
	writeFileSync(`${dir}/_sidebar.md`, `**<p style="margin-left: 15px;">${name}</p>**\n${loop(dir)}`);
};

console.log(`Generated sidebar for ${count} files in ${Date.now() - startTime}ms`);