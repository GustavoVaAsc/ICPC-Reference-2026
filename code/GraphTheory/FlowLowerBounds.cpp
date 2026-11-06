// Flow with lower bounds / circulation: reduction to ordinary max flow (use Dinic).
// Edge u->v with [lo, hi]: add edge u->v with capacity hi-lo; excess[v] += lo; excess[u] -= lo.
// Super source S, super sink T: for each v, excess[v] > 0 -> edge S->v (cap excess[v]);
//                                           excess[v] < 0 -> edge v->T (cap -excess[v]).
// Feasible circulation iff maxflow(S,T) == sum of positive excess (all S edges saturated).
// s-t flow with bounds: add edge t->s with capacity INF, run the above for feasibility;
//   feasible flow value = flow on the t->s edge. For the MAX s-t flow, then remove edge t->s
//   (and S,T) and run maxflow(s,t) on the residual; answer = value before + this.
//   For MIN flow: after feasibility, remove t->s, run maxflow(t,s); min = value - that flow.
// Flow on original edge = lo + flow on the reduced edge.
