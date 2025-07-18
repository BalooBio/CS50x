SELECT title FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON people.id = stars.person_id
    WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence')
    GROUP BY title
    HAVING COUNT(*)>1;
