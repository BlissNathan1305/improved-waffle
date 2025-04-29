const accessKey = 'YOUR_UNSPLASH_ACCESS_KEY'; // Replace with your key

async function searchImages() {
  const query = document.getElementById('query').value;
  const res = await fetch(`https://api.unsplash.com/search/photos?query=${query}&client_id=${accessKey}`);
  const data = await res.json();

  const results = document.getElementById('results');
  results.innerHTML = '';
  data.results.forEach(img => {
    const image = document.createElement('img');
    image.src = img.urls.small;
    results.appendChild(image);
  });
}