/* Closest pair of Points. Sweep-Line Approach
**/
struct point{double x, y;};
struct cmp_x{
    bool operator ()(const point &a, const point &b){
        return a.x < b.x;
    }
};
struct cmp_y{
    bool operator ()(const point &a, const point &b){
        return a.y < b.y;
    }
};

double dist(point a, point b){
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

int N, last;
double min_dist = 1e10;
point P[MX];
set <point, cmp_y> S;

int main(void){

    scanf("%d", &N);
    for(int i=1; i<=N; i++)
        scanf("%lf%lf", &P[i].x, &P[i].y);

    sort(P+1, P+N+1, cmp_x()), last++;

    for(int i=1; i<=N; i++){
        for( ; last < i && P[i].x - P[last].x >= min_dist; last++)
            S.erase( S.find(P[last]) );

        auto lo = S.lower_bound((point){P[i].x, P[i].y - min_dist});
        auto hi = S.upper_bound((point){P[i].x, P[i].y + min_dist});

        for( ; lo!=hi; lo++)
            min_dist = min(min_dist, dist(*lo, P[i]));

        S.insert(P[i]);
    }
    printf("%.4lf\n", min_dist);

  return 0;
 }
