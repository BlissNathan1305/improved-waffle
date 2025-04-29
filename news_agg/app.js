const apiKey = 'YOUR_NEWS_API_KEY'; // Replace this with your actual API key
const url = `https://newsapi.org/v2/top-headlines?country=us&apiKey=${apiKey}`;

fetch(url)
  .then(res => res.json())
  .then(data => {
    const container = document.getElementById('news-container');
    container.innerHTML = '';
    data.articles.forEach(article => {
      const div = document.createElement('div');
      div.innerHTML = `
        <h2>${article.title}</h2>
        <p>${article.description || 'No description available'}</p>
        <a href="${article.url}" target="_blank">Read more</a>
        <hr/>
      `;
      container.appendChild(div);
    });
  })
  .catch(err => {
    document.getElementById('news-container').innerHTML = 'Failed to fetch news.';
    console.error(err);
  });
